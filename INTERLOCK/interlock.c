#include<pic.h>
__CONFIG(0X2CE4);
 
void delay (unsigned int count)
{
while(--count);
}

int fst=0;
int rst=0;

void main()
{
PORTA=0X00;
PORTD=0X00;
TRISD=0X00;
TRISA=0X07;
ANSEL=ANSELH=0X00;

while(1)
{

if(fst==0 && RA0==1)
{
while(RA0);
delay(10000);
RD0=1;
rst++;

}
if (rst==0 && RA1==1)
{
while(RA1);
delay(10000);
RD1=1;
fst++;
}
if (RA2==1)
{
while(RA2);
delay(10000);
fst=rst=0;
PORTD=0X00;
}
}
}

