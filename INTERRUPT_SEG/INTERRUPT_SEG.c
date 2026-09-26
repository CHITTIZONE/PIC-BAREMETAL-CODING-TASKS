#include<pic.h>
__CONFIG(0x2CE4);


void delay (unsigned int count ){
	while(count--);
	}
	
int i;
int j;	
unsigned char seg[10]={0X3F,0X06,0X5B,0X4F,0X66,0X6D,0X7D,0X07,0X7F,0X6F};
	
	void interrupt isr()
		{
	if(INTF==1){
	for (int j=i;j>0;j--){
	PORTD=seg[j];
	delay(1000000);
	}
	}
	INTF=0;
	}
void main()
{
PORTB=0X00;
TRISB=0X01;
PORTD=0X00;
TRISD=0X00;
ANSEL=ANSELH=0x00;
INTE=1;
GIE=1;
for (i=0;i<10;i++){
//j=10-1-i;
PORTD=seg[i];
delay(1000000);
}
}


	