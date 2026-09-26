/*
 * File:   newmain.c
 * Author: robor
 *
 * Created on August 19, 2026, 3:29 PM
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

unsigned char n[]="CHITTI";
unsigned char m='c';
void main(){
    PORTA=PORTC=0x00;
    TRISA=0x03;
    TRISC=0X00;
    ANSEL=ANSELH=0X00;
    SYNC=0;
    BRG16=0;
    BRGH=1;
    SPBRG=25;
    TXEN=1;
    SPEN=1;
    while(1){
        if(RA0==1){
            while(RA0);
            TXREG=m;
            while(TXIF==0);
        }
        if(RA1==1){
            while(RA1);
            for(int i=0;n[i]!='\0';i++){
                TXREG=n[i];
                while(TXIF==0);
            }
        }
    }}