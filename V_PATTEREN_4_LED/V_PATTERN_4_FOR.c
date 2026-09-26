#include<pic.h>

void delay(unsigned int count)
{
	while(--count);
	}
	void led()
{
    int i;

    PORTD = 0x00;

    for(i=0; i<4; i++)
    {
        if(i==0)
        {
            RD0 = 1;
            delay(10000);

            RD1 = 1;
            delay(10000);
        }
        else if(i==1)
        {
            RD2 = 1;
            delay(10000);

            RD3 = 1;
            delay(10000);
        }
        else if(i==2)
        {
            RD4 = 1;
            delay(10000);

            RD5 = 1;
            delay(10000);
        }
        else if(i==3)
        {
            RD6 = 1;
            delay(10000);

            RD7 = 1;
            delay(10000);
        }
    }
}
	
	void main(){
		PORTD=0x00;
		TRISD=0X00;
		while(1)
		{
		led();
}
	}