/*
 * File:   pwm.c
 * Author: robor
 *
 * Created on August 5, 2026, 12:49 PM
 */


#include <xc.h>

void pwm(unsigned int duty)
{
    CCPR1L=duty>>2;
    DC1B1=duty&0x02;
    DC1B0=duty&0x01;
}

void main(){
    PORTC=TRISC=0x00;
    T2CON=0X05;
    TMR2=0;
    PR2=124;
    CCP1CON=0X0C;
    while(1){
        for(int i=0; i<100;i++){
            for (int j=0;j<150;j++){
                pwm(i);
            }
        }
    }
}
