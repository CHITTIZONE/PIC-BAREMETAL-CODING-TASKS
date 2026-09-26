#include<pic.h>
__CONFIG(0x2CE4);


void delay(unsigned int count)
	{
	while(count--);
	}
	void main(){
		PORTD=0X00;
		TRISD=0X00;
		PORTA=0X00;
		TRISA=0X01;
		ANSEL=ANSELH=0X00;
while(1){
if(RA0==1)
{
PORTD=0XFF;
delay(1000);
}
else
{
PORTD=0X00;
delay(1000);
}
	}
	}