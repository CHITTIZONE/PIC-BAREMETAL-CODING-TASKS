#include<pic.h>
__CONFIG(0X2CE4);
void delay(unsigned int count){
	while(--count);
	}
	void f()
{
		int i;
		for (i=0;i<=8;i++)
			{
			if(i==1)RD0=1,RD7=1;
            else if(i==2)RD1=1,RD6=1;
			else if(i==3)RD2=1,RD5=1;
			else if(i==4)RD3=1,RD4=1;
			else if(i==5)RB7=1,RB6=1;
			else if(i==6)RB4=1,RB5=1;
			else if(i==7)RB3=1,RB2=1;
			else if(i==8)RB1=1,RB0=1;
delay(100000);
}
			PORTD=0X00;
PORTB=0X00;
			}
void r(){
		int i;
		for (i=8;i>0;i--)
		{
			if(i==1)RD0=1,RD7=1;
            else if(i==2)RD1=1,RD6=1;
			else if(i==3)RD2=1,RD5=1;
			else if(i==4)RD3=1,RD4=1;
			else if(i==5)RB7=1,RB6=1;
			else if(i==6)RB4=1,RB5=1;
			else if(i==7)RB3=1,RB2=1;
			else if(i==8)RB1=1,RB0=1;
delay(100000);
}
			PORTD=0X00;
PORTB=0X00;
			}
	
	void main()
		{
			PORTA=0X00;
			PORTB=0X00;
			PORTD=0X00;
			TRISA=0X03;
            TRISB=0X00;
			TRISD=0X00;
			ANSEL=ANSELH=0X00;
			while(1){
if(RA0==1){
    f();
    while(RA0);
}
else if(RA1==1){
    r();
    while(RA1);
}
}
	}

				