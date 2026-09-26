#include <pic.h>
__CONFIG(0X2CE4);

void delay(unsigned int count)
{
    while(--count);
}

int mode = 0;

void main()
{
    PORTD = 0x00;
    PORTA = 0x00;

    TRISD = 0x00;
    TRISA = 0x07;      
    ANSEL = 0x00;
    ANSELH = 0x00;

   while(1)
{
    if(RA2)
{
    //while(RA3);
    delay(100000000);
    mode = !mode;
}

if(mode == 0)
{
    if(RA0) RD0 = 1;
    if(RA1) RD0 = 0;
}
else
{
    if(RA0) RD0 = 0;
    if(RA1) RD0 = 1;
}
}
}