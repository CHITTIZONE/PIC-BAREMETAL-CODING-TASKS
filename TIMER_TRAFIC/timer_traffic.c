#include<pic.h>
__CONFIG(0x2CE4);

unsigned int count=0;
void main(){
PORTA=0X00;
TRISA=0X00;
ANSEL=ANSELH=0X00;
OPTION_REG=0X07;
while(1)
	{
if(T0IF==1){
count++;
T0IF=0;
}
if (count==0){
RA2=0;
RA0=1;
}
else if(count==15){
RA0=0;
RA1=1;
}
else if(count==30){
RA1=0;
RA2=1;
}
else if (count==45){
count=0;}
}
}