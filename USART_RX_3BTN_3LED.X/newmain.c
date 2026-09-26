/*
 * File:   newmain.c
 * Author: robor
 *
 * Created on August 26, 2026, 12:29 PM
 */
 
 
// PIC16F887 Configuration Bit Settings

// 'C' source line config statements

// CONFIG1
#pragma config FOSC = EXTRC_CLKOUT// Oscillator Selection bits (RC oscillator: CLKOUT function on RA6/OSC2/CLKOUT pin, RC on RA7/OSC1/CLKIN)
#pragma config WDTE = ON        // Watchdog Timer Enable bit (WDT enabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = ON       // RE3/MCLR pin function select bit (RE3/MCLR pin function is MCLR)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = ON       // Brown Out Reset Selection bits (BOR enabled)
#pragma config IESO = ON        // Internal External Switchover bit (Internal/External Switchover mode is enabled)
#pragma config FCMEN = ON       // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is enabled)
#pragma config LVP = ON         // Low Voltage Programming Enable bit (RB3/PGM pin has PGM function, low voltage programming enabled)

// CONFIG2
#pragma config BOR4V = BOR40V   // Brown-out Reset Selection bit (Brown-out Reset set to 4.0V)
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits (Write protection off)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>
void delay(unsigned long int count){
    while(--count);
}
unsigned char d;

void LCD(unsigned int a, unsigned int b){
    RE0=a;
    PORTD=b;
    RE1=1;
    delay(10);
    RE1=0;
    delay(10);
}

void main(){
    PORTD=PORTE=0x00;
    TRISE=TRISD=0x00;
    TRISA=0x00;
    PORTA=0x00;
    TRISC=0x00;
    PORTC=0x00;
    TRISC=0x80;
    ANSEL=ANSELH=0x00;
    CREN=1;
    SYNC=0;
    SPEN=1;
    SPBRG=25;
    BRGH=1;
 BRG16=0;
 LCD(0,0X38);
 LCD(0,0X0E);
 LCD(0,0X80);
 while(1){
        while(RCIF==0);
        d=RCREG;
        LCD(1,d);
        if(d=='A'){
            RA5=1;
            delay(100000);
            RA5=0;
            d=0;
            
        }
        if(d=='B'){
            RA6=1;
            delay(100000);
            RA6=0;
    d=0;    
        }
        if(d=='C'){
            RA7=1;
            delay(1000000);
            RA7=0;
            d=0;
        }
    }
    }
    
