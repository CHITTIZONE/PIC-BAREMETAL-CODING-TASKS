/*
 * File:   FULL_DUPLEX_MASTER.c
 * Author: robor
 *
 * Created on August 28, 2026, 2:50 PM
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
unsigned char c;
void delay(unsigned int count)
{
    while(--count);
}

void LCD(unsigned int a, unsigned int b){
    RE0=a;
    PORTD=b;
    RE1=1;
    delay(10);
    RE1=0;
    delay(10);
}
void main(){
    // btn input;
    PORTB=0x00;
    TRISB=0x01;
    //LCD 
    PORTD=0x00;
    TRISD=0x00;
    PORTE=0x00;
    TRISE=0x00;
    //MASTER CONFIG
    //PORTA=0x00;
    //TRISA=0x10;
    PORTC=0x00; // MAIN CHANGE
    TRISC=0x10;// MAIN CHANGE
    SSPCON=0x20;// MAIN CHANGE
    SSPSTAT=0x00;// MAIN CHANGE
    
    //LCD ON;
    LCD(0,0x38);
    LCD(0,0x0E);
    LCD(0,0x80);
    
    ANSEL=ANSELH=0x00;
    while(1){
        if(RB0==1){
            while(RB0);
            SSPBUF='A';
            while(SSPIF==0);
            delay(10);
            c=SSPBUF;
            LCD(1,c);
            SSPIF==0;
        }
    }
}