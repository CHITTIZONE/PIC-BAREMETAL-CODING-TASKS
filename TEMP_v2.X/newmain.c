/*
 * File:   newmain.c
 * Author: robor
 *
 * Created on August 17, 2026, 10:36 AM
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
char c[]="Temp=";
unsigned int cc=0; 

void delay(unsigned int count)
{
    while (--count)
}
void LCD(unsigned int a , unsigned int b){
    RE0=a;
    PORTD=b;
    RE1=1;
    delay(10);
    RE1=0;
    delay(10);
    
}

void temp(unsigned int a){
    
    LCD(0,0X80);
    for(int i=0;c[i]!='\0';i++){
    LCD(1,c[i]);
    }
    LCD(1,((a/1000)%10)+'0');
    LCD(1,((a/100)%10)+'0');
    LCD(1,((a/10)%10)+'0');
    LCD(1,((a%10)+'0');
    LCD(1,'c');
}

void farhent(unsigned int a){
    LCD(0,0x80);
    b=(a*1.8)+32;
    for (int i=0;c[i]!='\0';i++){
        LCD(1,c[i]);
    }
    LCD(1,((a/1000)%10)+'0');
    LCD(1,((a/100)%10)+'0');
    LCD(1,((a/10)%10)+'0');
    LCD(1,((a/10)%10)+'0');
    LCD(1,'F');
    }
}
void voltage(float a){
    char s[]="LOW VOLTAGE";
    if a<=1.2{
        LCD(0,0xC0);
        for (int i=0;s[i]!='\0';i++)
        {
            LCD(1,s[i]);
        }
    }
}

void main()