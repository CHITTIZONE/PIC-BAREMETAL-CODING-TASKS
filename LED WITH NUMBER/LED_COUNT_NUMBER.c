#include<pic.h>
__CONFIG(0X2CE4);
void delay(unsigned int count){
	while(--count);
	}
	
	void LED(int i)
{


    if(i==1) RD0=1;
    else if(i==2) RD1=1;
    else if(i==3) RD2=1;
    else if(i==4) RD3=1;
    else if(i==5) RD4=1;
    else if(i==6) RD5=1;
    else if(i==7) RD6=1;
    else if(i==8) RD7=1;
}
		
		
	
	void main()
	{
		int c=0;
		PORTA=0X00;
		PORTD=0X00;
		TRISD=0X00;
		TRISA=0X03;
ANSEL=ANSELH=0X00;
while(1){	
if(RA0==1)
			{
while(RA0==1);
delay(1000);
			c++;
			}
if (RA1==1){
while (RA1==1);
delay(1000);
				LED(c);
			}
if(c>0&& RA0==1){
while(RA0==1);
PORTD-0X00;
}
	}
	}
