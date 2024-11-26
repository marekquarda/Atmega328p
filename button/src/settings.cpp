/*
 * settings.cpp
 *
 * Created: 2024-11-01 20:00:32
 * Author : Marek Xara Quarda
 */ 

#include "settings.h"
#include "lcd.h"

// ISR for port B
ISR(PCINT1_vect) {
    cli();
    lcd_clear();
    uint16_t timer = 0;
    // Execute instruction for PCINT8 to PCINT14
    // Pins C0 - C7 
    // Button Up
    if ((PINC & (1<<PINC0))==0) {
       // lcd_write_word("Pin C0,");
        while((PINC & (1<<PINC0))==0) {
            _delay_ms(1);
            timer++;
        }
        if (timer < 500UL) {// unsigned long
                // sigle click
                shortButtonSet();
        } else {
                // button hold
                longButtonSet();
        }
    }
    // Button Set
    if ((PINC & (1<<PINC2))== 0) {
//        lcd_write_word("Pin C2,");
        while((PINC & (1<<PINC2))==0) {
            timer++;
            _delay_ms(1);
        }
        if (timer > BTN_DEBOUCE) {
            if (timer < 500UL) {// unsigned long
                // sigle click
                shortButtonSet();
            } else {
                // button hold
                longButtonSet();
            }
        }
    }
    sei();
}

void initInterruptSettings(void) {
    // Button Settings
    // Pins as input
    DDRC &= ~(1<<PORTC0);
    DDRC &= ~(1<<PORTC2);
    // Pulup pins
    PORTC |= (1<<PORTC0) | (1<<PORTC2);

    // Enable PCMSK1 (Group 1: PCINT8 to PCINT14)
    PCICR |= _BV(PCIE1);
    //PCICR |= 0b00000010;
    PCMSK1 |= (1<<PCINT8) | (1<<PCINT10);
    //PCMSK1 |= 0b0000001;
    
    // red led
    DDRD |=  0b00000010;
    PORTD |= 0b00000000;
    // green led
    DDRB |=  0b00100000;
    PORTB |= 0b00000000;
    sei();          // Global Interrupts
}

void shortButtonUp() {
    lcd_write_word("Short Up");
    _delay_ms(2000);
}

void longButtonUp() {
    lcd_write_word("Long Up");
    _delay_ms(2000);
}

void shortButtonSet() {
    lcd_write_word("Short Set");
    _delay_ms(2000);
}

void longButtonSet() {
    lcd_write_word("Long Set");
    _delay_ms(2000);
}



