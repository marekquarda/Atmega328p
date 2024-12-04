/*
 * settings.cpp
 *
 * Created: 2024-11-01 20:00:32
 * Author : Marek Xara Quarda
 */ 

#include "buttonsets.h"
#include "micromenu.h"
#include "lcd.h"

ButtonValues select = BTN_NONE;
MenuPosition position = DEFAULT_POS;

// ISR for port B
ISR(PCINT1_vect) {
    cli();
    uint16_t timer = 0;
    // Button Up
    if ((PINC & (1<<PINC0))==0) {
        while((PINC & (1<<PINC0))==0) {
            _delay_ms(1);
            timer++;
        }
        if (timer > BTN_DEBOUCE) {
            if (timer < 700UL) {// unsigned long
                // sigle click
                select = BTN_SHORT_UP;
            } else {
                // button hold
                select = BTN_LONG_UP;
            }
        }
    }
    // Button Set
    if ((PINC & (1<<PINC2))== 0) {
        while((PINC & (1<<PINC2))==0) {
            timer++;
            _delay_ms(1);
        }
        if (timer > BTN_DEBOUCE) {
            if (timer < 700UL) {// unsigned long
                // sigle click
                select = BTN_SHORT_SET;
            } else {
                // button hold
                select = BTN_LONG_SET;
            }
        }
    }
    ChooseItem();
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
    //sei();          // Global Interrupts
}

enum ButtonValues GetButtonPress(void) {
    return select;
}

enum MenuPosition GetMenuPosition(void) {
    return position;
}

void SetMenuPosition(MenuPosition pos) {
    position = pos;
}

void ChooseItem() {
    switch (GetButtonPress())
    {
    case BTN_SHORT_UP: 
        Menu_Navigate(MENU_PREVIOUS);
        break;
    case BTN_LONG_UP: 
        Menu_Navigate(MENU_PARENT);
        break;
    case BTN_SHORT_SET: 
        Menu_Navigate(MENU_NEXT); 
        break; 
    case BTN_LONG_SET:
        Menu_Navigate(MENU_CHILD);
        break;
    default:
        break;
    }
}



