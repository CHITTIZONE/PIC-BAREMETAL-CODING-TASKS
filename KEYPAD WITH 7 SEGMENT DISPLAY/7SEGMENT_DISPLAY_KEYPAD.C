#include<pic.h>
__CONFIG(0X2CE4);
void delay(unsigned int count){
while(--count);
}

int i=0;
int j=0;
int sum=0;
unsigned char seg[10]={0X3F,0X06,0X5B,0X4F,0X66,0X6D,0X7D,0X07,0X7F,0X6F};
      
void t(){
for(j=0;j<2000;j++){
RD1=1;
RD0=0;
PORTB=seg[(sum/10)];
delay(100);
PORTB=0;

RD0=1;
RD1=0;
PORTB=seg[(sum%10)];
delay(100);
PORTB=0;
}
delay(1000000000);
}


void main ()
{
PORTA=0X00;
TRISA=0XF0;
PORTB=0X00;
TRISB=0X00;
PORTD=0X00;
TRISD=0X00;
ANSEL=ANSELH=0X00;

while(1)
{

// segment c1
RA1=1;RA2=0;RA3=0;
if (RA7==1)
{
while(RA7);
PORTB=seg[1];
i=1;
}
else if(RA6==1)
{
while(RA6);
PORTB=seg[4];
i=4;
}
else if(RA5==1)
{while(RA5);
PORTB=seg[7];
i=7;
}
else if(RA4==1)
{while(RA4);
sum+=i;
}


//segment c2

RA1=0;RA2=1;RA3=0;
if (RA7==1)
{while(RA7);
PORTB=seg[2];
i=2;
}
else if(RA6==1)
{while(RA6);
PORTB=seg[5];
i=5;
}
else if (RA5==1)
{while(RA7);
PORTB=seg[8];
i=8;}
else if(RA4==1)
{while(RA4);
PORTB=seg[0];
i=0;
}


//segment c3

RA1=0;RA2=0;RA3=1;
if (RA7==1)
{while(RA7);
PORTB=seg[3];
}
else if(RA6==1)
{while(RA6);
PORTB=seg[6];
i=6;}
else if(RA5==1)
{while(RA5);
PORTB=seg[9];
i=9;}
else if(RA4==1)
{
t();
//delay(10000);
}
delay(100);
PORTB=0;
}

}

	