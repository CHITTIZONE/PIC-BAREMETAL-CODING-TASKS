#include <pic.h>
__CONFIG(0X2CE4);

/* ---------- Global variables ---------- */
unsigned int count = 0;                 // Timer tick counter, incremented in ISR

unsigned char st[]  = "STARTED";
unsigned char sto[] = "STOPED";
unsigned char w[]   = "WATER";
unsigned char Ri[]  = "RINSE";
unsigned char C[]   = "COMPLETED";
unsigned char t[]   = "TIME=";

/* ---------- Function prototypes ---------- */
void delay(unsigned int c);
void LCD(unsigned int a, unsigned int b);
void stop(void);
void start(void);
void Lt(unsigned int value);
void interrupt isr(void);

/* ---------- Simple busy-wait delay ---------- */
void delay(unsigned int c)
{
    while (c--);
}

/* ---------- LCD write function ----------
   a = 0 -> command, a = 1 -> data
   b    -> byte to send                    */
void LCD(unsigned int a, unsigned int b)
{
    RE0 = a;         // Register select: 0 = command, 1 = data
    PORTD = b;        // Data/command byte on PORTD
    RE1 = 1;          // Enable pulse high
    delay(100);
    RE1 = 0;          // Enable pulse low (latches data)
    delay(100);
}

/* ---------- Interrupt Service Routine ---------- */
void interrupt isr(void)
{
    // External stop button on RB1 (interrupt-on-change)
    if (RB1 == 1)
    {
        stop();
        RB1 = 0;
    }

    // Timer0 overflow interrupt - used as the time base
    if (T0IF == 1)
    {
        count++;
        T0IF = 0;
        TMR0 = 131;   // Reload Timer0 for consistent interval
    }
}

/* ---------- Stop routine ----------
   Turns off outputs and displays "STOPED" */
void stop(void)
{
    RE2 = 0;
    RE3 = 0;

    for (int i = 0; sto[i] != '\0'; i++)
    {
        LCD(1, sto[i]);
    }
}

/* ---------- Countdown timer display ----------
   Shows a single-digit countdown (4..1) on the LCD
   at a fixed cursor position once "value" ticks pass */
void Lt(unsigned int value)
{
    static unsigned char sec = 4;

    if (count >= value)
    {
        count = 0;
        LCD(0, 0xC5);        // Move cursor to position after "TIME="
        LCD(1, '0' + sec);   // Print current digit

        if (sec > 1)
            sec--;
    }
}

/* ---------- Start / main sequence controller ----------
   Runs through washing stages based on elapsed count */
void start(void)
{
    if (count == 125)
    {
        RE2 = 1;              // Turn on stage 1 output (e.g. wash motor)
        LCD(0, 0x01);          // Clear display
        LCD(0, 0x80);          // Cursor to line 1, position 0

        for (int i = 0; st[i] != '\0'; i++)
        {
            LCD(1, st[i]);
            Lt(125);
        }
    }
    else if (count == 250)
    {
        RE2 = 1;
        LCD(0, 0x01);
        LCD(0, 0x80);

        for (int i = 0; w[i] != '\0'; i++)
        {
            LCD(1, w[i]);
            Lt(250);
        }
    }
    else if (count == 1000)
    {
        RE2 = 0;
        RE3 = 1;               // Turn on stage 2 output (e.g. rinse motor)
        LCD(0, 0x01);
        LCD(0, 0x80);

        for (int i = 0; Ri[i] != '\0'; i++)
        {
            LCD(1, Ri[i]);
            Lt(1000);
        }
    }
    else if (count == 1250)
    {
        RE2 = 0;
        RE3 = 0;
        LCD(0, 0x01);
        LCD(0, 0x80);

        for (int i = 0; C[i] != '\0'; i++)
        {
            LCD(1, C[i]);
            Lt(1250);
        }
    }
}

/* ---------- Main ---------- */
void main(void)
{
    /* Port initialization */
    PORTD = 0x00;
    PORTE = 0x00;
    PORTB = 0x00;

    TRISD = 0x00;     // PORTD all output (LCD data)
    TRISE = 0x00;     // PORTE all output (LCD control + relay outputs)
    TRISB = 0x07;     // RB0-RB2 as inputs (buttons)

    ANSEL = ANSELH = 0x00;   // All pins digital

    /* LCD initialization */
    LCD(0, 0x38);      // Function set: 8-bit, 2 line, 5x7
    LCD(0, 0x0E);      // Display ON, cursor ON
    LCD(0, 0x0C);      // Display ON, cursor OFF

    /* Timer0 setup */
    OPTION_REG = 0x05; // Timer0, prescaler assigned, 1:64
    TMR0 = 131;        // Initial reload value

    /* Interrupt setup */
    GIE  = 1;          // Global interrupt enable
    T0IE = 1;          // Timer0 overflow interrupt enable
    RBIE = 1;          // Port B change interrupt enable
    IOCB1 = 1;         // Interrupt-on-change enabled for RB1

    while (1)
    {
        // Redundant polling backup for Timer0 (also handled in ISR)
        if (T0IF == 1)
        {
            TMR0 = 131;
            count++;
            T0IF = 0;
        }

        if (RB0 == 1)
        {
            start();
        }
        else if (RB2 == 1)
        {
            main();   // Restart (note: recursive call - see caution below)
        }
    }
}