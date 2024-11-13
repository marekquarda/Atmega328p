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
    lcd_write_word("Interrupt ...");
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
                shortButtonUp();
            } else {
                // button hold
                longButtonUp();
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
    // Pins as input
    DDRC &= 0b11111010;
    // Pulup pins
    PORTC = 0b00000101;

    // Enable PCMSK1 (Group 1: PCINT8 to PCINT14)
    PCICR |= _BV(PCIE1);
    //PCICR |= 0b00000010;
    PCMSK1 |= (1<<PCINT8) | (1<<PCINT10);
    //PCMSK1 |= 0b0000001;
    // Button Setting
    // red led
    DDRD |=  0b00000010;
    PORTD |= 0b00000000;
    // green led
    DDRB |=  0b00100000;
    PORTB |= 0b00000000;
    sei();
}

void shortButtonUp() {
    lcd_clear();
    lcd_write_word("Short Up");
  //  PORTB = 0b00000000;
  // _delay_ms(500);
   PORTB = 0b00100000;
  // _delay_ms(500);
}

void longButtonUp() {
    lcd_clear();
    lcd_write_word("Long Up");
    PORTB = 0b00000000;
    _delay_ms(5);
    PORTB = 0b00100000;
    _delay_ms(5);
}

void shortButtonSet() {
    lcd_clear();
    lcd_write_word("Short Set");
    PORTD = 0b00000010;
// _delay_ms(5);
// PORTD = 0b00000000;
// _delay_ms(5);
}

void longButtonSet() {
    lcd_clear();
    lcd_write_word("Long Set");
    PORTD = 0b00000010;
    _delay_ms(5);
    PORTD = 0b00000000;
    _delay_ms(5);
}


