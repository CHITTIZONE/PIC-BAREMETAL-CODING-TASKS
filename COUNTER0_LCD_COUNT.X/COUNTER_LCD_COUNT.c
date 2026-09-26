/*
 * File:   COUNTER_LCD_COUNT.c
 * Author: robor
 *
 * Created on August 4, 2026, 2:15 PM
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

unsigned int c=0;
unsigned char cc[]="count:";
void delay(unsigned int count){
    while(count--);
}

void LCD(unsigned int a, unsigned int b)
{
    RE0=a;
    PORTD=b;
    RE1=1;
    delay(1000);
    RE1=0;
    delay(1000);
}

void main(){
    PORTD=PORTE=0x00;
    TRISD=TRISE=0x00;
   PORTC=0x00; TRISC=0x01;
    ANSEL=ANSELH=0X00;
    T1CON=0X03;
    TMR1=0;
    LCD(0,0X38);
    LCD(0,0X0E);
    LCD(0,0X0C);
    while(1){
        c=TMR1;
       LCD(0,0x80);
       //LCD(0,0x01);
       for (int i=0;cc[i]!='\0';i++){
           LCD(1,cc[i]);
           //delay(1000);
       }
       LCD(1,c+'0');
    }
}
