#include<pic.h>
__CONFIG(0X2CE4);

void delay(unsigned int count){
	while(count--);
	}
	
	//pattern=1
void pattern1( )
{
PORTD=0x00;
TRISD=0x00;

while(1)
{
int i;
i=1;
RD0=i;
RD1=i;
RD2=i;
RD3=i;
RD4=i;
RD5=i;
RD6=i;
RD7=i;
delay(100000);
i=0;
RD0=i;
RD1=i;
RD2=i;
RD3=i;
RD4=i;
RD5=i;
RD6=i;
RD7=i;
delay(100000);
}
}

void main()
{
 pattern1();
}		
			
	