/*
 * settings.cpp
 *
 * Created: 2024-11-01 20:00:32
 * Author : Marek Xara Quarda
 */ 

#include "settings.h"

// ISR for port B
ISR(PCINT1_vect) {
    uint16_t timer = 0;
    // Execute instruction for PCINT8 to PCINT14
    // Pins C0 - C7 
    // Button Up
    if (PINC & 0b00000001) {
        while ((bit_is_clear(PINC, PC0))) { // button hold down
            timer++;
            _delay_ms(1);
        }
        if (timer > BTN_DEBOUCE) {
            if (timer < 500UL) {// unsigned long
                // sigle click
            } else {
                // button hold
            }
        }
    }
    // Button Set
    if (PINC & 0b00000100) {
        while ((bit_is_clear(PINC, PC2))) { // button hold down
            timer++;
            _delay_ms(1);
        }
        if (timer > BTN_DEBOUCE) {
            if (timer < 500UL) {// unsigned long
                // sigle click
            } else {
                // button hold
            }
        }
    }
}


void initInterruptSettings(void) {
    // Enable PCMSK1 (Group 1: PCINT8 to PCINT14)
    PCICR |= 0b00000010;
    PCMSK1 |= 0b0000001;
}