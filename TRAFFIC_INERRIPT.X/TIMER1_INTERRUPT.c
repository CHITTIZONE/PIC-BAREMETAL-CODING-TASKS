/*
 * File:   digital_thermometer.c
 * Author: robor
 *
 * ============================================================
 *  WHAT THIS PROGRAM DOES (plain English)
 * ============================================================
 *  - Reads temperature from an LM35 on AN0 (RA0), 10-sample averaged.
 *  - The LCD does NOT update on every single reading. It waits for
 *    the reading to stay steady (within +/-1C, to tolerate normal
 *    ADC noise) for 15 seconds before showing it as "confirmed". If
 *    the temperature drifts to a genuinely different value at any
 *    point during that wait, the 15 second countdown restarts.
 *  - RE2 LED is tied to that SAME settle state:
 *      -> blinking  = a reading is currently settling (mid-wait)
 *      -> steady ON = the current confirmed value is stable
 *  - Battery on AN1 (RA1), wired directly (no divider, 0-5V at the
 *    pin): monitored on an INTERRUPT-DRIVEN schedule, not a slow
 *    poll. Timer0 (the same ~4ms tick used for the button) flags a
 *    "check due" event roughly once a second. The main loop reacts
 *    to that flag immediately - reads AN1 and, if below 1.5V, flashes
 *    "LOW POWER" on line 2 right away for ~1.5s, non-blocking. The
 *    actual ADC read is kept in the main loop (not inside the ISR
 *    itself) so it can never collide with the temperature conversion,
 *    which shares the same ADC hardware.
 *  - Display layout:
 *      Line 1 -> "TEMP: 222C" / "TEMP: 222F" (or just "TEMP" while
 *                still settling)
 *      Line 2 -> blank normally, "LOW POWER" during the battery flash
 *  - RB0 button (external pulldown wiring, idle=LOW, press=HIGH):
 *      -> HOLD 5 seconds  -> powers the display on (ONLY the first
 *                            time, from an off state - a stray 5s+
 *                            hold while already running is ignored,
 *                            so it can't "restart" the unit).
 *      -> HOLD 3 seconds, WHILE ALREADY POWERED ON -> toggles
 *                            Celsius/Fahrenheit the INSTANT the
 *                            hold crosses 3s (no need to release
 *                            the button first). If a confirmed
 *                            reading already exists it's redrawn
 *                            right away in the new unit; if not
 *                            (still mid-settle), the preference is
 *                            just stored and the LCD keeps showing
 *                            "TEMP" until the first confirm. Only
 *                            fires once per hold.
 *      -> A 3s+ hold that happens to be the VERY FIRST hold from
 *         an off state does NOT also toggle units - it only powers
 *         on, exactly like before. The toggle only arms once the
 *         unit is already on.
 *      -> released before 3 seconds -> ignored.
 *
 *  PIN MAP:
 *    RA0 (AN0)  -> LM35 output
 *    RA1 (AN1)  -> Battery sense line (0-5V range at the pin, direct)
 *    PORTD      -> LCD data D0-D7 (8-bit mode)
 *    RE0        -> LCD RS
 *    RE1        -> LCD EN     (LCD RW tied to GND on hardware)
 *    RE2        -> Status LED
 *    RB0        -> Push button (external pulldown)
 *
 *  NOTE: _XTAL_FREQ assumes internal oscillator at 4 MHz.
 * ============================================================
 */

// CONFIG1
#pragma config FOSC = INTRC_NOCLKOUT
#pragma config WDTE = OFF
#pragma config PWRTE = ON
#pragma config MCLRE = ON
#pragma config CP = OFF
#pragma config CPD = OFF
#pragma config BOREN = OFF
#pragma config IESO = ON
#pragma config FCMEN = ON
#pragma config LVP = OFF
// CONFIG2
#pragma config BOR4V = BOR40V
#pragma config WRT = OFF

#include <xc.h>

#define _XTAL_FREQ 4000000   // 4 MHz internal osc

// ---- LCD pin aliases ----
#define LCD_DATA  PORTD
#define LCD_RS    RE0
#define LCD_EN    RE1
#define LED_READY RE2

// ---- Button ----
#define BTN       RB0

// Timer0 ticks at ~4.1ms each (1:16 prescaler @4MHz, see Timer0_Init).
#define THREE_SEC_TICKS    732
#define FIVE_SEC_TICKS     1220

#define BATTERY_LOW_MV    1500   // 1.5V threshold
// Battery check is now interrupt-paced off Timer0 (~4.1ms/tick),
// not off main-loop passes - this is how often a background ADC
// conversion on AN1 gets kicked off.
#define BATTERY_CHECK_TICKS     244   // ~1s @ ~4.1ms/tick
#define BATTERY_NOTIFY_PASSES     5   // ~1.5s flash duration
#define TEMP_SETTLE_PASSES       50   // ~15s - how long a reading must hold steady
#define TEMP_TOLERANCE_C          1   // +/-1C jitter still counts as "the same" reading

/* ============================================================
 *  GLOBAL VARIABLES (shared with the ISR -> must be volatile)
 * ============================================================ */
volatile unsigned int  press_ticks    = 0;
volatile unsigned char btn_is_down    = 0;
volatile unsigned char power_on_ev    = 0;
volatile unsigned char unit_toggle_ev = 0;
volatile unsigned char toggle_armed   = 0;  // per-hold guard so 3s fires only once
volatile unsigned char powered_on     = 0;  // read by ISR, written by main -> volatile

// ---- Interrupt-driven battery check scheduling ----
volatile unsigned int  batt_check_ticks = 0;  // Timer0-paced countdown to next battery check
volatile unsigned char batt_check_due   = 0;  // set by the ISR every ~1s; main loop reacts to it

unsigned char show_fahren = 0;

/* ============================================================
 *  LCD LOW-LEVEL FUNCTIONS
 * ============================================================ */
void LCD_Pulse(void)
{
    LCD_EN = 1;
    __delay_us(50);
    LCD_EN = 0;
    __delay_us(50);
}

void LCD_Cmd(unsigned char cmd)
{
    LCD_RS   = 0;
    LCD_DATA = cmd;
    LCD_Pulse();
    __delay_ms(2);
}

void LCD_Char(unsigned char data)
{
    LCD_RS   = 1;
    LCD_DATA = data;
    LCD_Pulse();
    __delay_us(100);
}

void LCD_String(const char *str)
{
    while (*str)
    {
        LCD_Char(*str);
        str++;
    }
}

void LCD_Goto(unsigned char row, unsigned char col)
{
    unsigned char addr = (row == 0) ? (0x80 + col) : (0xC0 + col);
    LCD_Cmd(addr);
}

void LCD_Clear(void)
{
    LCD_Cmd(0x01);
    __delay_ms(2);
}

void LCD_Init(void)
{
    __delay_ms(20);
    LCD_Cmd(0x38);
    LCD_Cmd(0x0C);
    LCD_Cmd(0x06);
    LCD_Clear();
}

/* ============================================================
 *  ADC SETUP AND READ
 * ============================================================ */
void ADC_Init(void)
{
    ANSEL  = 0x03;
    ANSELH = 0x00;

    TRISA0 = 1;
    TRISA1 = 1;

    ADCON1bits.ADFM = 1;
    ADCON0bits.ADCS = 0b10;
    ADCON0bits.ADON = 1;
}

unsigned int ADC_Read(unsigned char channel)
{
    ADCON0 &= 0xC3;              // clear CHS3:CHS0 (bits 5-2) - 4-bit field on this chip
    ADCON0 |= (channel << 2);
    __delay_us(30);
    ADCON0bits.GO_nDONE = 1;
    while (ADCON0bits.GO_nDONE);
    return ((unsigned int)ADRESH << 8) | ADRESL;
}

int Read_Temperature_C(void)
{
    unsigned long sum = 0;
    unsigned char i;

    for (i = 0; i < 10; i++)
    {
        sum += ADC_Read(0);
        __delay_ms(10);
    }

    unsigned int avg  = (unsigned int)(sum / 10);
    int temp_c = (int)((unsigned long)avg * 500UL / 1024UL);
    return temp_c;
}

int CtoF(int celsius)
{
    return (celsius * 9) / 5 + 32;
}

// AN1 is wired directly to the battery sense line (no divider), so
// the raw 10-bit ADC count maps straight across the full 0-5V range.
// Divisor is 1023 (max 10-bit reading). Averages 4 samples with a
// real settle delay after the channel switch, since this runs right
// after Read_Temperature_C() which leaves the ADC on AN0.
unsigned int Read_Battery_mV(void)
{
    unsigned char i;
    unsigned long sum = 0;

    ADCON0 &= 0xC3;
    ADCON0 |= (1 << 2);   // select AN1
    __delay_us(100);      // let the S&H cap settle to the new channel

    for (i = 0; i < 4; i++)
    {
        sum += ADC_Read(1);
        __delay_ms(2);
    }

    unsigned int adc = (unsigned int)(sum / 4);
    unsigned long mv = (unsigned long)adc * 5000UL / 1023UL;
    return (unsigned int)mv;
}

/* ============================================================
 *  TIMER0 - ~4ms tick, used only to time the button hold
 * ============================================================ */
void Timer0_Init(void)
{
    OPTION_REGbits.T0CS = 0;
    OPTION_REGbits.PSA  = 0;
    OPTION_REGbits.PS   = 0b011;  // 1:16 prescaler -> ~4.1ms per overflow @4MHz
    TMR0 = 0;
    T0IE = 1;
    T0IF = 0;
}

/* ============================================================
 *  RB0 / INT0 - button press/release timing
 * ============================================================ */
void RB0_Init(void)
{
    TRISB0 = 1;
    OPTION_REGbits.nRBPU  = 1;
    OPTION_REGbits.INTEDG = 1;   // idle=LOW, press=HIGH -> start watching rising edge
    INTF = 0;
    INTE = 1;
}

/* ============================================================
 *  ISR
 * ============================================================ */
void __interrupt() ISR(void)
{
    if (T0IE == 1 && T0IF == 1)
    {
        T0IF = 0;

        if (btn_is_down)
        {
            press_ticks++;

            // Live 3s toggle - only arms once the unit is already
            // powered on, so this can never fire on the very first
            // (power-on) hold. Fires exactly once per hold, the
            // moment the hold crosses 3s - no release required.
            if (powered_on && toggle_armed == 0 &&
                press_ticks >= THREE_SEC_TICKS)
            {
                unit_toggle_ev = 1;
                toggle_armed   = 1;
            }

            if (press_ticks >= FIVE_SEC_TICKS && power_on_ev == 0)
            {
                power_on_ev = 1;
            }
        }

        // ---- Battery: interrupt-paced check scheduling ----
        // Once powered on, roughly once a second, flag that a battery
        // check is due. The actual ADC read happens in the main loop
        // (never inside this ISR) so it can't collide with the
        // foreground temperature conversion, which shares the same
        // ADC hardware.
        if (powered_on)
        {
            batt_check_ticks++;
            if (batt_check_ticks >= BATTERY_CHECK_TICKS)
            {
                batt_check_ticks = 0;
                batt_check_due   = 1;
            }
        }
    }

    if (INTE == 1 && INTF == 1)
    {
        INTF = 0;

        if (OPTION_REGbits.INTEDG == 1)
        {
            // rising edge -> PRESSED
            btn_is_down   = 1;
            press_ticks   = 0;
            power_on_ev   = 0;
            toggle_armed  = 0;
            OPTION_REGbits.INTEDG = 0;
        }
        else
        {
            // falling edge -> RELEASED
            btn_is_down = 0;
            OPTION_REGbits.INTEDG = 1;
            // No release-time toggle check needed anymore - the 3s
            // toggle (when applicable) already fired live above.
        }
    }
}

/* ============================================================
 *  DISPLAY HELPER
 * ============================================================ */
void Display_Temp(int value, unsigned char is_fahrenheit)
{
    char buf[17];
    unsigned char idx = 0;
    unsigned char neg = 0;

    const char *prefix = "TEMP: ";
    while (*prefix) { buf[idx++] = *prefix++; }

    if (value < 0) { neg = 1; value = -value; }

    char digits[4];
    unsigned char dcount = 0;
    if (value == 0) { digits[dcount++] = '0'; }
    while (value > 0 && dcount < 4)
    {
        digits[dcount++] = (value % 10) + '0';
        value /= 10;
    }

    if (neg) buf[idx++] = '-';
    while (dcount > 0) { buf[idx++] = digits[--dcount]; }
    buf[idx++] = 0xDF;
    buf[idx++] = is_fahrenheit ? 'F' : 'C';
    buf[idx++] = ' ';
    buf[idx++] = ' ';
    buf[idx] = '\0';

    LCD_Goto(0, 0);
    LCD_String(buf);
}

// Small helper so both the toggle handler and the confirm handler
// redraw the same way, in whichever unit is currently selected.
void Redraw_Current(int celsius_value)
{
    if (show_fahren)
        Display_Temp(CtoF(celsius_value), 1);
    else
        Display_Temp(celsius_value, 0);
}

int abs_int(int v)
{
    return (v < 0) ? -v : v;
}

void main(void)
{
    PORTA = 0x00;
    PORTD = 0x00;
    PORTE = 0x00;

    TRISD  = 0x00;
    TRISE0 = 0;
    TRISE1 = 0;
    TRISE2 = 0;

    ADC_Init();
    Timer0_Init();
    RB0_Init();
    LCD_Init();

    PEIE = 1;
    GIE  = 1;

    LED_READY = 0;

    LCD_Clear();
    LCD_Goto(0, 0);
    LCD_String("Hold BTN 5s..");

    unsigned char notify_count = 0;

    // ---- Temperature "settle and confirm" state ----
    int candidate_temp   = 0;
    int confirmed_temp   = 0;
    unsigned char settle_passes  = 0;
    unsigned char have_confirmed = 0;

    while (1)
    {
        // ---- 5 second hold: power on, ONLY the first time ----
        if (power_on_ev == 1)
        {
            power_on_ev = 0;

            if (!powered_on)
            {
                powered_on = 1;
                settle_passes  = 0;
                have_confirmed = 0;

                LCD_Clear();
                LCD_Goto(0, 0);
                LCD_String("TEMP");
                __delay_ms(500);
            }
            // else: already running - ignore, nothing resets
        }

        // ---- 3 second hold, fired live while still held (only
        //      possible once the unit is already powered on -
        //      see the ISR gate) : toggle C/F ----
        if (unit_toggle_ev == 1)
        {
            unit_toggle_ev = 0;
            if (powered_on)
            {
                show_fahren = !show_fahren;
                // Only redraw a numeric value if we actually have a
                // confirmed one. Before the first 15s settle finishes
                // there's nothing real to show yet, so the unit
                // preference is stored silently and the display just
                // keeps showing "TEMP" until the first confirm.
                if (have_confirmed)
                {
                    Redraw_Current(confirmed_temp);
                }
            }
        }

        if (!powered_on)
        {
            continue;
        }

        // ---- Take a fresh reading every pass ----
        int temp_c = Read_Temperature_C();

        // ---- Settle-and-confirm logic (with +/-1C tolerance for noise) ----
        if (abs_int(temp_c - candidate_temp) <= TEMP_TOLERANCE_C && settle_passes > 0)
        {
            // still within tolerance of what we're already watching
            if (settle_passes < TEMP_SETTLE_PASSES)
            {
                settle_passes++;
            }
        }
        else if (settle_passes == 0)
        {
            // first sample after a reset - just start watching it
            candidate_temp = temp_c;
            settle_passes  = 1;
        }
        else
        {
            // genuinely different - restart the wait against the new value
            candidate_temp = temp_c;
            settle_passes  = 1;
        }

        unsigned char is_settled = (settle_passes >= TEMP_SETTLE_PASSES);

        if (is_settled && (have_confirmed == 0 || candidate_temp != confirmed_temp))
        {
            confirmed_temp = candidate_temp;
            have_confirmed = 1;
            Redraw_Current(confirmed_temp);
        }

        // ---- LED: tied directly to the settle state above ----
        // Blinking while a reading is still settling, steady once it's
        // confirmed and stable.
        if (is_settled)
        {
            LED_READY = 1;   // steady glow - current value is confirmed/stable
        }
        else
        {
            LED_READY = 1;
            __delay_ms(100);
            LED_READY = 0;   // blink - still settling
        }

        // ---- Battery: reacts to the interrupt-driven "check due" flag ----
        // Timer0 flags this roughly once a second; the moment it's due,
        // we read AN1 and act immediately if it's low - no waiting on a
        // long poll interval like before.
        if (batt_check_due)
        {
            batt_check_due = 0;
            unsigned int batt_mv = Read_Battery_mV();
            if (batt_mv < BATTERY_LOW_MV)
            {
                notify_count = BATTERY_NOTIFY_PASSES;
            }
        }

        if (notify_count > 0)
        {
            LCD_Goto(1, 0);
            LCD_String("LOW POWER   ");
            notify_count--;
            if (notify_count == 0)
            {
                LCD_Goto(1, 0);
                LCD_String("            "); // clear line 2 when the flash ends
            }
        }

        __delay_ms(200);
    }
}
