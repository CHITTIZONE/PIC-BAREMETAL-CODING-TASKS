/*
 * File:   DUAL_MASTER.c
 * Author: robor
 *
 * Created on August 28, 2026, 2:32 PM
 */



// PIC16F887 Configuration Bit Settings

// 'C' source line config statements

// CONFIG1
#pragma config FOSC = INTRC_NOCLKOUT// Oscillator Selection bits (INTOSCIO oscillator: I/O function on RA6/OSC2/CLKOUT pin, I/O function on RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = ON       // Power-up Timer Enable bit (PWRT enabled)
#pragma config MCLRE = ON       // RE3/MCLR pin function select bit (RE3/MCLR pin function is MCLR)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = OFF      // Brown Out Reset Selection bits (BOR disabled)
#pragma config IESO = ON        // Internal External Switchover bit (Internal/External Switchover mode is enabled)
#pragma config FCMEN = ON       // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is enabled)
#pragma config LVP = OFF        // Low Voltage Programming Enable bit (RB3 pin has digital I/O, HV on MCLR must be used for programming)

// CONFIG2
#pragma config BOR4V = BOR40V   // Brown-out Reset Selection bit (Brown-out Reset set to 4.0V)
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits (Write protection off)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>

unsigned char a="HELLO";
unsigned char b[32];
unsigned int index2=0;
unsigned int index=0;

void delay(unsigned int count){
    while(--count);
}

void lcd(unsigned int a, unsigned int b )
{
    RC0=a;
    PORTB=b;
    RC1=1;
    delay(10);
    RC1=0;
    delay(10);
}
void main()
{
PORTB=0x00;
TRISB=0x00;
PORTA=0x00;
TRISA=0x20;
RA5=1;
PORTC=0x00;
TRISC=0x18;
PORTD=0x00;
TRISD=0x07;
PORTC=0x00;
PORTE=0XFF;
TRISE=0X00;
ANSEL=ANSELH=0x00;
SSPCON=0x20;
SSPSTAT=0x00;
while(1)
{
        if (RD0==1){
            while(RD0);
            RE0=0;
            RE1=1;
            RE2=1;
        for(int i=0;a[i]!='\0';i++)
        {
       SSPBUF=a[i];
       delay(10000);
       while(SSPIF==0);
        }

        }
        else if (RD1==1){
            while(RD1);
            RE0=1;
            RE1=0;
            RE2=1;
            for (int i=0;a[i]!='\0';i++)
            {
                SSPBUF=a[i];
                delay(10000);
                while(SSPIF==0);
              b[index2]=SSPBUF;
            LCD(1,b[index2]);
            index++;
            SSPIF=0;
            }
            }
        else if (RD2==1){
            while(RD2);
            RE0=1;
            RE1=1;
            RE2=0;
            for (int i=0;a[i]!='\0';i++){
                SSPBUF=a[i];
                delay(1000);
                while(SSPIF==0);
                
            }
    }
            
}
}
}

