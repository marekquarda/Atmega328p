#include <avr/io.h>
#include <util/delay.h>


int main() 
{
    // init 
    // red led
    DDRD =  0b00000010;
    PORTD = 0b00000000;
    // green led
    DDRB =  0b00100000;
    PORTB = 0b00000000;

    while(1) {
        PORTD = 0b00000010;
        PORTB = 0b00000000;
        _delay_ms(500);
        PORTD = 0b00000000;
        PORTB = 0b00100000;
        _delay_ms(500);
    }

    return 0;
}