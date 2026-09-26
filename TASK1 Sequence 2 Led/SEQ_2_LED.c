#include<pic.h>
__CONFIG(0X2CE4);

// delay syntax
void delay(unsigned int count){
while (count--);
}

// main function
void main()
{
PORTD=0X00;// port d FULL intial as 0
TRISD=0X00;// port d full as op 0 for output int for input 1248
 while(1)
{
RD0=1;
delay(500000);
RD0=0;
delay(10000);
RD1=1;
delay(10000000);
RD1=0;
delay(10000);
}
}
