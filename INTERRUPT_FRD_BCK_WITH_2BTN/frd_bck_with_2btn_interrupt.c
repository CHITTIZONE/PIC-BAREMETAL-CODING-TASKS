#include<pic.h>
__CONFIG(0x2CE4);

void delay(unsigned int count){
	
while(count--);
}
unsigned int i=0;
unsigned char seg[10]={0X3F,0X06,0X5B,0X4F,0X66,0X6D,0X7D,0X07,0X7F,0X6F};
void frd(){
	if(i<9){
	i++;
	PORTD=seg[i];
		delay(100000);
		
		}
}
		
void rev(){
	if (i>0)
{	i--;
		PORTD=seg[i];
		delay(100000);
		}
		
}		
void interrupt isr(){
	if(RB0==1){
		frd();
		}
		if (RB1==1)
			{
			rev();
			}
}
			
void main()
	{
	PORTB=0X00;
	PORTD=0X00;
	TRISB=0X03;
	TRISD=0X00;
	ANSEL=ANSELH=0X00;
	GIE=1;
	RBIE=1;
	IOCB0=1;
	IOCB1=1;
	PORTD=seg[i];
	while(1){
	}
}	
	
	