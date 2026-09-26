#include<pic.h>
__CONFIG(0x2CE4);

	
unsigned int count=0;
		
void interrupt isr ()
	{
if(T0IF==1){
count++;
T0IF=0;
TMR0=131;
}
}

void main()
{
PORTA=0x00;
TRISA=0x00;
ANSEL=ANSELH=0x00;

GIE=1;
T0IE=1;
TMR0=131;
OPTION_REG=0x05;

while(1){
if (count==125){
RA0=1;
}
if(count==250){
RA0=0;
count=0;
}
}
}