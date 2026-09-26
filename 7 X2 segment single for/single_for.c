#include<pic.h>
__CONFIG(0X2CE4);

void delay( unsigned int count)
{
	while(--count);
	}
	
int i;
int j;
int k;


unsigned char seg[10]={0X3F,0X06,0X5B,0X4F,0X66,0X6D,0X7D,0X07,0X7F,0X6F};	

void main()
{
	PORTB=0X00;
	PORTA=0X00;
	TRISA=0X03;
	TRISB=0X00;
PORTD=0X00;
TRISD=0X00;
	
	ANSEL=ANSELH=0X00;
while (1){


if(RA0==1){
//while(RA0);

for (i=0;i<100;i++)
{
j=99-i;
for(k=0;k<20;k++){

                        
RD1=1;
                        RD2=1;
						RD3=1;
						RD0=0;
                        PORTB=seg[i/10];
                        delay(1000);
PORTB=0;
                        
                        
                        
RD2=1;
						RD3=1;
						RD0=1;
RD1=0;
                        PORTB=seg[i%10];
                        delay(1000);

PORTB=0;						
					
RD1=1;
						RD3=1;
						RD0=1;
RD2=0;	
                        PORTB=seg[j/10];
                        delay(1000);

PORTB=0;
                       
                        RD1=1;
                        RD2=1;
						RD0=1;
 RD3=0;
                        PORTB=seg[j%10];
                        delay(1000);

PORTB=0;

}
}
}
}
}
	
    	