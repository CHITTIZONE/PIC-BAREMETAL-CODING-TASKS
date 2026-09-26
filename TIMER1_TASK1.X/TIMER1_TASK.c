/*
 * File:   newmain.c
 * Author: robor
 *
 * Created on July 31, 2026, 11:45 AM
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

volatile unsigned int count=0;    // fix: shared with ISR -> must be volatile
volatile unsigned int c=0;        // fix: shared with ISR -> must be volatile
volatile unsigned int period=0;   // fix: holds the on/off time captured at RB2 press, used to blink RA3 continuously

unsigned char seg[10]={0X3F,0X06,0X5B,0X4F,0X66,0X6D,0X7D,0X07,0X7F,0X6F};	

unsigned char Tp(unsigned int on_time)
{
    if(on_time==0) return 0;               // fix: avoid % by zero if RB2 never pressed / c is 0
    if((count % (2 * on_time)) < on_time)
        return 1;  
    else
        return 0;  
}

void __interrupt() timer1()
{
    if(TMR1IF==1)
    {
        count++;
       TMR1IF=0;
       TMR1=53036;
    }
    if(RBIF==1){
    if(RB0==1){
        while(RB0);
        c++;
        //RB0=0;
    }
    if (RB1==1&&c>0)
    {
        while(RB1);
        c--;
        //RB0=0;
    }
    if (RB2==1){
        while(RB2);
        period=c*600;   // fix: just capture the current c as the new blink period; don't set RA3 here
    }
    RBIF=0;
    
    }
}

void main(){
    PORTD=PORTE=PORTA=0x00;
    TRISD=TRISE=TRISA=0x00;
    PORTB=0X00;
    TRISB=0X07;
    ANSEL=ANSELH=0X00;
    
    // TMR CONFIG
    T1CON=0X31;
    TMR1=53036;
    
    //INTERRUPT LOGIN
    IOCB0=1;
    IOCB1=1;
    IOCB2=1;
    RBIE=1; 
    
    TMR1IE=1;
    GIE=1;
    PEIE=1;
 //PORTA=0x00;   
    while(1){
    RA0 = Tp(12);   
    RA1 = Tp(21);   
    RA2 = Tp(35);   
    RA3 = Tp(period);   // fix: continuously blink RA3 at the last-captured period, holds until RB2 pressed again
    //for (int i=0; i<20;i++){
    RE1=1;
    RE0=0;
    PORTD=seg[(c/10)%10];
    Tp(1);
    PORTD=0;
   
    
    RE0=1;
    RE1=0;
    PORTD=seg[c%10];
    Tp(1);
    PORTD=0;
    //Tp(1000000000);
    //}
}
    
    
    
}