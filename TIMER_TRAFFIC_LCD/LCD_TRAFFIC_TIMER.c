#include<pic.h>
__CONFIG(0X2CE4);
#define RED_TIME     5
#define YELLOW_TIME  5
#define GREEN_TIME   10
#define TMR0_PRELOAD          131
#define OVERFLOWS_PER_SECOND  125

unsigned char timer0_tick(void)
{
    if(T0IF == 1)
    {
        T0IF = 0;
        TMR0 = TMR0_PRELOAD;
        return 1;
    }
    return 0;
}

void timer0_wait(unsigned int overflows)
{
    unsigned int done = 0;
    while(done < overflows)
    {
        if(timer0_tick())
        {
            done++;
        }
    }
}

void LCD(unsigned int a, unsigned int b)
{
    RE0 = a;
    PORTD = b;
    RE1 = 1;
    timer0_wait(1);   
    RE1 = 0;
    timer0_wait(1);
}


void LCD_puts(const unsigned char *s)
{
    while(*s != '\0')
    {
        LCD(1, *s);
        s++;
    }
}

void LCD_putnum(unsigned int num)
{
    if(num >= 10)
    {
        LCD(1, (num/10)%10 + '0');   // tens digit
        LCD(1, (num%10) + '0');   // ones digit
    }
    else
    {
        LCD(1, num + '0');        // single digit, no leading zero
    }
}

void show_state(const unsigned char *colour_name, unsigned int seconds_left)
{
    LCD(0, 0x01);   
    LCD(0, 0x80);  
    LCD_puts(colour_name);

    LCD(0, 0xC0);  
    LCD_puts("TIME=");
    LCD_putnum(seconds_left);
    LCD(1, 's');
}

enum {STATE_RED, STATE_YELLOW, STATE_GREEN};

void main(void)
{
    PORTA = 0x00;  
    TRISA = 0x00;
    PORTB = 0x00;  
    TRISB = 0x00;
    PORTD = 0x00;  
    TRISD = 0x00;
    PORTE = 0x00;  
    TRISE = 0x00;
    ANSEL = ANSELH = 0x00;

    OPTION_REG = 0x05;   
    TMR0 = TMR0_PRELOAD;  

    LCD(0, 0x38);   // 2 lines, 5x7 font
    LCD(0, 0x0E);   // display on, cursor on
    LCD(0, 0x0C);

    unsigned char state = STATE_RED;
    unsigned int seconds_left = RED_TIME;
    unsigned int tick_count = 0;   // counts raw Timer0 overflows within the current second

    RA0 = 1; RA1 = 0; RA2 = 0;              // start on red
    show_state("RED", seconds_left);

    while(1)
    {
        /* wait here for Timer0 to overflow. it takes OVERFLOWS_PER_SECOND
           overflows (125, with prescaler=64 and TMR0 preloaded to 131)
           to add up to one real second */
        if(timer0_tick())
        {
            tick_count++;

            if(tick_count < OVERFLOWS_PER_SECOND)
            {
                continue;            // not a full second yet, keep counting
            }
            tick_count = 0;          // one real second has now passed

            seconds_left--;                 // one second has passed

            if(seconds_left == 0)
            {
               
                if(state == STATE_RED)
                {
                    state = STATE_YELLOW;
                    RA0 = 0; RA1 = 1; RA2 = 0;
                    seconds_left = YELLOW_TIME;
                    show_state("YELLOW", seconds_left);
                }
                else if(state == STATE_YELLOW)
                {
                    state = STATE_GREEN;
                    RA0 = 0; RA1 = 0; RA2 = 1;
                    seconds_left = GREEN_TIME;
                    show_state("GREEN", seconds_left);
                }
                else 
                {
                    state = STATE_RED;
                    RA0 = 1; RA1 = 0; RA2 = 0;
                    seconds_left = RED_TIME;
                    show_state("RED", seconds_left);
                }
            }
            else
            {
                
                LCD(0, 0xC0);
                LCD_puts("TIME=");
                LCD_putnum(seconds_left);
                LCD(1, 's');
            }
        }
    }
}