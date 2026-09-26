#include<pic.h>
__CONFIG(0X2CE4);

void delay(unsigned int count)
	{
	while(--count);
	}

unsigned char seg[10]={0X3F,0X06,0X5B,0X4F,0X66,0X6D,0X7D,0X07,0X7F,0X6F};	
int i=0;
int j=0;
int k;

	

void main()
	{
PORTB=0X00;
TRISB=0X00;
PORTA=0X00;
PORTD=0X00;
TRISD=0X00;
TRISA=0X03;
ANSEL=ANSELH=0X00;

while (1)
{

if(RA0==1)
{
while(RA0);

for (i=10;i>0;i--)
{
for (j=10;j>0;j--){
for(k=0;k<200;k++)
                    {
                        
                       
                        RD1=1;
						RD0=0;
                        PORTB=seg[i];
                        delay(200);

                        
                        RD0=1;
                        RD1=0;
                        PORTB=seg[j];
                        delay(200);
                    }
}
	}
}
if(RA1==1)
{
while(RA1);

for (i=0;i<10;i++)
{
for (j=0;j<10;j++)
{
for(k=0;k<200;k++)
                    {
                        
                       
                        RD1=1;
						RD0=0;
                        PORTB=seg[i];
                        delay(200);

                        
                        RD0=1;
                        RD1=0;
                        PORTB=seg[j];
                        delay(200);
                    }
}
	}
}
}
	}




		
	