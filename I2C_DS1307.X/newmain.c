/*
 * File:   I2C_START.c
 * Author: robor
 *
 * Created on August 29, 2026, 12:05 PM
 *
 * Purpose: Read current time (seconds, minutes, hours) from a
 *          DS1307 RTC over I2C using the PIC16F887 MSSP module.
 */

// PIC16F887 Configuration Bit Settings
#pragma config FOSC = INTRC_NOCLKOUT
#pragma config WDTE = OFF
#pragma config PWRTE = ON
#pragma config MCLRE = ON
#pragma config CP = OFF
#pragma config CPD = OFF
#pragma config BOREN = OFF
#pragma config IESO = ON
#pragma config FCMEN = ON
#pragma config LVP = OFF
#pragma config BOR4V = BOR40V
#pragma config WRT = OFF

#include <xc.h>

#define _XTAL_FREQ 8000000UL   // adjust to match your internal oscillator setting

#define DS1307_ADDR 0xD0       // DS1307 base address, write = 0xD0, read = 0xD1

/* ---------- Low-level I2C master helpers ---------- */

void I2C_Init(void)
{
    TRISC3 = 1;      // SCL pin as input (hardware controls direction)
    TRISC4 = 1;      // SDA pin as input
    SSPCON = 0x28;   // SSPEN=1, I2C Master mode
    SSPCON2 = 0x00;
    SSPSTAT = 0x00;  // slew rate control on (standard 100kHz mode)
    SSPADD = 9;      // baud rate generator: ~100kHz @ 8MHz Fosc -> ((8MHz/4)/(100kHz)) - 1 = 9
}

void I2C_Wait(void)
{
    // Wait until the current I2C operation (and the bus) is idle
    while ((SSPSTAT & 0x04) || (SSPCON2 & 0x1F));
}

void I2C_Start(void)
{
    I2C_Wait();
    SEN = 1;         // initiate Start condition
    while (SEN);     // wait for hardware to clear SEN (start complete)
}

void I2C_RepeatedStart(void)
{
    I2C_Wait();
    RSEN = 1;        // initiate Repeated Start condition
    while (RSEN);
}

void I2C_Stop(void)
{
    I2C_Wait();
    PEN = 1;         // initiate Stop condition
    while (PEN);
}

// Sends one byte on the bus, returns 1 if slave ACKed, 0 if it NACKed
unsigned char I2C_Write(unsigned char data)
{
    I2C_Wait();
    SSPBUF = data;
    while (SSPIF == 0);   // wait for transmission to finish
    SSPIF = 0;
    return !ACKSTAT;      // ACKSTAT = 0 means slave ACKed
}

// Reads one byte from the slave.
// ack = 1 -> master sends ACK (more bytes to come)
// ack = 0 -> master sends NACK (last byte, tells slave to stop sending)
unsigned char I2C_Read(unsigned char ack)
{
    unsigned char data;

    I2C_Wait();
    RCEN = 1;             // enable receive mode
    while (RCEN);         // wait until byte fully shifted in
    data = SSPBUF;

    I2C_Wait();
    ACKDT = ack ? 0 : 1;  // 0 = ACK bit, 1 = NACK bit
    ACKEN = 1;            // trigger the ack/nack sequence
    while (ACKEN);

    return data;
}

/* ---------- Helper to convert BCD (DS1307's native format) to decimal ---------- */
unsigned char BCD_to_Dec(unsigned char bcd)
{
    return ((bcd >> 4) * 10) + (bcd & 0x0F);
}

/* ---------- DS1307 time read ---------- */
void DS1307_ReadTime(unsigned char *sec, unsigned char *min, unsigned char *hour)
{
    I2C_Start();
    I2C_Write(DS1307_ADDR);     // 0xD0 = write mode, points to the chip
    I2C_Write(0x00);            // set the register pointer to 0x00 (seconds register)

    I2C_RepeatedStart();        // restart the bus without releasing it, to switch to read mode
    I2C_Write(DS1307_ADDR | 1); // 0xD1 = read mode

    *sec  = I2C_Read(1);        // read seconds register, ACK to request next byte
    *min  = I2C_Read(1);        // read minutes register, ACK to request next byte
    *hour = I2C_Read(0);        // read hours register, NACK because this is the last byte

    I2C_Stop();

    // DS1307 stores values in BCD, so convert before using them
    *sec  = BCD_to_Dec(*sec & 0x7F);   // mask off the clock-halt bit (bit 7) of the seconds reg
    *min  = BCD_to_Dec(*min);
    *hour = BCD_to_Dec(*hour & 0x3F);  // mask off 12/24-hr mode bits if present
}

void main(void)
{
    unsigned char seconds, minutes, hours;

    PORTC = 0x00;
    TRISC = 0x18;    // RC3/RC4 as inputs for I2C (hardware overrides during I2C ops anyway)

    I2C_Init();

    while (1)
    {
        DS1307_ReadTime(&seconds, &minutes, &hours);

        // At this point seconds/minutes/hours hold the current time in decimal.
        // Send them to an LCD, UART, or however you display data in your project.

        __delay_ms(500);  // simple polling delay; replace with Timer interrupt if needed
    }
}