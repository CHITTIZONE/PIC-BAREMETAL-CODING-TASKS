/*
 * File:   newmain.c
 * Author: robor
 *
 * Created on August 18, 2026, 3:35 PM
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

volatile int count=0,data=0;
void delay(unsigned int count){
    while(--count);
}
void LCD(unsigned int a, unsigned int b)
{
    RE0=a;
    PORTD=b;
    RE1=1;
    delay(10);
    RE1=0;
    delay(10);
}
void __interrupt()isr()
{
    if(ADIF==1){
        if(data>512){
        count++;
        RA1=1;
        ADIF=0;
    }else {
        RA1=0;
        count=0;
        
    }
   
    }
 ADIF=0;
}
    
void main(){
    ADIE=1;
    PEIE=1;
    GIE=1;
    PORTA=PORTD=PORTE=0x00;
TRISD=TRISE=0x00;
TRISA=0x01;
ANSEL=0x01;
ANSELH=0x00;
ADCON0=0x81;
ADCON1=0x80;

LCD(0,0X38);
LCD(0,0X0E);
LCD(0,0X0C);
while(1){
    GO=1;
    data = ADRESL+(ADRESH<<8);
    LCD(0,0X80);
    LCD(1,((count/1000)%10)+'0');
    LCD(1,((count/100)%10)+'0');
    LCD(1,((count/10)%10)+'0');
    LCD(1,(count%10)+'0');
   
}
}
