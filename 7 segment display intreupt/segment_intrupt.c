#include<pic.h>
__CONFIG(0X2CE4);

void delay(unsigned int count)
	{
	while(--count);
	}

unsigned char seg[10]={0X3F,0X06,0X5B,0X4F,0X66,0X6D,0X7D,0X07,0X7F,0X6F};	
int i,j;

void intr()
{
delay(10000);
for(j=i;j>=0;j--)
{
PORTB=seg[j];
delay(100000);
}
}	

void main()
	{
PORTB=0X00;
TRISB=0X00;
PORTA=0X00;
TRISA=0X03;
ANSEL=ANSELH=0X00;

while (1)
{

if(RA0==1)

{
while(RA0);
for (i=0;i<10;i++)

{
if (RA1==1){
intr();
break;
}
else {
PORTB=seg[i];
delay(100000);

}
}

}
//else{
PORTB=0X00;
//}
}
}
		
	