#include<pic.h>
__CONFIG(0X2CE4);

void delay(unsigned int count){
	while(count--);
	}
	
	void main(){
		PORTD=0X00;
		TRISD=0X00;
		while(1)
		{
			RD0=1;
			delay(100000);
			RD0=0;
			delay(100000);
			}
			}
			