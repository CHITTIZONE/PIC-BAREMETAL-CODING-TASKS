/*
 * File:    ADC_LED.c
 * Author:  robor
 *
 * Created on August 10, 2026, 11:15 AM
 */

// CONFIG1
#pragma config FOSC = INTRC_NOCLKOUT// Oscillator Selection bits
#pragma config WDTE = OFF       // Watchdog Timer Enable bit
#pragma config PWRTE = ON       // Power-up Timer Enable bit
#pragma config MCLRE = ON       // RE3/MCLR pin function select bit
#pragma config CP = OFF         // Code Protection bit
#pragma config CPD = OFF        // Data Code Protection bit
#pragma config BOREN = OFF      // Brown Out Reset Selection bits
#pragma config IESO = ON        // Internal External Switchover bit
#pragma config FCMEN = ON       // Fail-Safe Clock Monitor Enabled bit
#pragma config LVP = OFF        // Low Voltage Programming Enable bit

// CONFIG2
#pragma config BOR4V = BOR40V   // Brown-out Reset Selection bit
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits

#include <xc.h>

unsigned int data = 0;
const unsigned char p[] = "Percentage :"; // Kept short to fit on 16x2 LCD line 2

void delay(unsigned int count) {
    while (--count);
}

void pwm(unsigned int duty) {
    CCPR1L = duty >> 2;
    DC1B1 = (duty >> 1) & 0x01; // Bit 1 shift fix
    DC1B0 = duty & 0x01;        // Bit 0 mask
}

void LCD(unsigned int a, unsigned int b) {
    RE0 = a;      // RS pin
    PORTD = b;    // Data port
    RE1 = 1;      // Enable pulse
    delay(100);
    RE1 = 0;
    delay(100);
}

unsigned int voltage(void) {
    return (unsigned int)(((unsigned long)data * 5000) / 1023);
}

unsigned int percentage(void) {
    return (unsigned int)(((unsigned long)data * 100) / 1023);
}

void main(void) {
    PORTD = PORTE = PORTC = 0x00;
    TRISD = TRISE = TRISC = 0x00;
    PORTA = 0x00;
    TRISA = 0x01;
    ANSEL = 0x01;
    ANSELH = 0x00;
    
    ADCON0 = 0x81; // AN0 enabled, ADC ON
    ADCON1 = 0x80; // Right justified
    
    T2CON = 0x05;  // Timer2 ON, Prescaler 1:4
    TMR2 = 0;
    PR2 = 124;     // PWM period
    CCP1CON = 0x0C;// PWM Mode
    
    LCD(0, 0x38);  // 8-bit mode, 2-line display
    LCD(0, 0x0C);  // Display ON, Cursor OFF

    while (1) {
        GO = 1;
        while (GO == 1);
        
        data = ((unsigned int)ADRESH << 8) | ADRESL;
        
        pwm(data);
        
        // Line 1: Voltage Output (e.g. 4887 mV)
        unsigned int m = voltage();
        LCD(0, 0x80); // Move cursor to Row 1, Col 1
        LCD(1, 'V');
        LCD(1, '=');
        LCD(1, (m / 1000) + '0');
        LCD(1, '.');
        LCD(1, ((m / 100) % 10) + '0');
        LCD(1, ((m / 10) % 10) + '0');
        LCD(1, (m % 10) + '0');
        

        // Line 2: Percentage Output (e.g. PCT: 100%)
        LCD(0, 0xC0); // Move cursor to Row 2, Col 1
        
        // Print string "PCT:"
        for (int i = 0; p[i] != '\0'; i++) {
            LCD(1, p[i]);
        }
        
        // Calculate and print percentage (0 - 100%)
        unsigned int pct = percentage();
        LCD(1, ((pct / 100) % 10) + '0'); // Hundreds digit
        LCD(1, ((pct / 10) % 10) + '0');  // Tens digit
        LCD(1, (pct % 10) + '0');         // Ones digit
        LCD(1, '%');
    }
}