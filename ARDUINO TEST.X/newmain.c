/*
 * File:   newmain.c
 * Author: robor
 *
 * Created on August 31, 2026, 9:57 AM
 */

#include <avr/io.h>
#include <util/delay.h>

int main(void) {
    // Set PD3 as output
    DDRD |= (1 << PD3);

    while (1) {
        // Turn LED ON (set PD3 high)
        PORTD |= (1 << PD3);
        _delay_ms(500);

        // Turn LED OFF (set PD3 low)
        PORTD &= ~(1 << PD3);
        _delay_ms(500);
    }
}
