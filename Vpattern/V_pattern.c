#include<pic.h>
__CONFIG(0X2CE4);

void delay(unsigned int count)
{
	while(count--);
	}
	
	void main()
	{
int i,j;
		PORTD=0X00;
		TRISD=0X00;
		
		while(1)
{
for (i=0;i<8;i++)
{
if (i==0)
{
RD0=1;
}
else if(i==1)
{
RD1=1;						
}
else if(i==2)
{
RD2=1;
}
else if(i==3)
{
RD3=1;
}
else if(i==4)
{
RD4=1;
}
else if(i==5)
{
RD5=1;
}
else if(i==6)
{
RD6=1;
}
else if(i==7)
{
RD7=1;
}
delay(100000);
}
for (i=8;i>=0;i--)
{
if (i==0)
{
RD0=0;
}
else if(i==1)
{
RD1=0;						
}
else if(i==2)
{
RD2=0;
}
else if(i==3)
{
RD3=0;
}
else if(i==4)
{
RD4=0;
}
else if(i==5)
{
RD5=0;
}
else if(i==6)
{
RD6=0;
}
else if(i==7)
{
RD7=0;
}
delay(100000);
}

}
}
