#include<pic.h>
__CONFIG(0x2CE4);
unsigned int count=0;
void main(){
PORTA=0x00;
TRISA=0x00;
ANSEL=ANSELH=0x00;
OPTION_REG=0x07;
while(1)
	{
if(T0IF==1)
{
count++;
T0IF=0;
}
if (count==15){
RA0=1;
}
if (count==30){
RA0=0;
count=0;
}
}
}