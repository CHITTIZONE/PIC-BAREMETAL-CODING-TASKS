#include<pic.h>
__CONFIG(0X2CE4);

void delay(unsigned int count)
	{
	while(--count);
	}
void main()
{
		PORTD=0X00;
		PORTA=0X00;
		TRISD=0X00;
		TRISA=0X03;
		
		ANSEL=ANSELH=0X00;
		
		while(1)
{
			if (RA0==1)
				{

RD0=1;
delay(10000);
}
if (RA1==1)
				{

RD1=1;
delay(10000);
}
				
else
 {
	PORTD=0X00;
}
}
}
	