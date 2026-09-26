#include<pic.h>
__CONFIG(0x2CE4);

int i=0;
unsigned int count=0;
unsigned char seg[10]={0X3F,0X06,0X5B,0X4F,0X66,0X6D,0X7D,0X07,0X7F,0X6F};

void main(){
PORTD=0x00;
TRISD=0x00;
ANSEL=ANSELH=0X00;
OPTION_REG=0X07;

while(1)
	{
if (T0IF==1)
	{
count++;
T0IF=0;
}
if(count==0){
PORTD=seg[i];
}
else if(count==15){
i++;
count=0;
}	
if(i==10){
i=0;
}
}
}
