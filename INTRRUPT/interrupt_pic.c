#include<pic.h>
__CONFIG(0x2CE4);

void delay(unsigned long int count){
while(count--);
}

void interrupt isr(){
	if (INTF==1){
		RA1=0;
		RA0=1;
		delay(100000);
		INTF=0;
		}
}
		void main(){
			TRISA=0x00;
			TRISB=0x01;
			PORTA=0x00;
			PORTB=0x00;
			ANSEL=ANSELH=0x00;
			INTE=1;
			GIE=1;
			while(1){
				RA0=0;
				RA1=1;
				}}
	