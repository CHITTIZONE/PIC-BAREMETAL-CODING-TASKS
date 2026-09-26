#include<pic.h>
__CONFIG(0X2CE4);

void delay(unsigned int count)
{
    while(--count);
}

void c();
void ic();
void chk();

int i=0;
int j[4];
int pos=0;          // Position of entered digit
int ck=0;
int check=1234;

unsigned char seg[10]={0X3F,0X06,0X5B,0X4F,0X66,0X6D,0X7D,0X07,0X7F,0X6F};

//---------------- Store Password ----------------//

void store()
{
    j[pos]=i;
    pos++;

    if(pos==4)
    {
        ck = j[0]*1000 +
             j[1]*100 +
             j[2]*10 +
             j[3];

        chk();

        pos=0;
        ck=0;
    }
}

//---------------- Password Check ----------------//

void chk()
{
    if(ck==check)
    {
        c();
    }
    else
    {
        ic();
    }
}

//---------------- Incorrect Password ----------------//

void ic()
{
    int x;

    for(x=0;x<200;x++)
    {
        RD1=1;RD2=1;RD3=1;RD0=0;
        PORTB=0X39;
        delay(100);

        RD0=1;RD2=1;RD3=1;RD1=0;
        PORTB=0X38;
        delay(100);

        RD0=1;RD1=1;RD3=1;RD2=0;
        PORTB=0X3F;
        delay(100);

        RD0=1;RD1=1;RD2=1;RD3=0;
        PORTB=0X6D;
        delay(100);
    }
}

//---------------- Correct Password ----------------//

void c()
{
    int x;

    for(x=0;x<2000;x++)
    {
        RD1=1;RD2=1;RD3=1;RD0=0;
        PORTB=0X3F;
        delay(100);

        RD0=1;RD2=1;RD3=1;RD1=0;
        PORTB=0X73;
        delay(100);

        RD0=1;RD1=1;RD3=1;RD2=0;
        PORTB=0X79;
        delay(100);

        RD0=1;RD1=1;RD2=1;RD3=0;
        PORTB=0X37;
        delay(100);
    }
}

//---------------- Main ----------------//

void main()
{
    PORTA=0X00;
    TRISA=0XF0;

    PORTB=0X00;
    TRISB=0X00;

    PORTD=0X00;
    TRISD=0X00;

    ANSEL=0X00;
    ANSELH=0X00;

    while(1)
    {

        //---------------- Column 1 ----------------//

        RA1=1;
        RA2=0;
        RA3=0;

        if(RA7)
        {
            while(RA7);
            i=1;
            store();
        }

        else if(RA6)
        {
            while(RA6);
            i=4;
            store();
        }

        else if(RA5)
        {
            while(RA5);
            i=7;
            store();
        }

        //---------------- Column 2 ----------------//

        RA1=0;
        RA2=1;
        RA3=0;

        if(RA7)
        {
            while(RA7);
            i=2;
            store();
        }

        else if(RA6)
        {
            while(RA6);
            i=5;
            store();
        }

        else if(RA5)
        {
            while(RA5);
            i=8;
            store();
        }

        else if(RA4)
        {
            while(RA4);
            i=0;
            store();
        }

        //---------------- Column 3 ----------------//

        RA1=0;
        RA2=0;
        RA3=1;

        if(RA7)
        {
            while(RA7);
            i=3;
            store();
        }

        else if(RA6)
        {
            while(RA6);
            i=6;
            store();
        }

        else if(RA5)
        {
            while(RA5);
            i=9;
            store();
        }

        delay(100);
    }
}