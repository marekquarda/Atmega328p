/*
 * main.c
 *
 * Scan for I2C devices on a ATmega358p 8 Mhz
 * Author : Marek Xara Quarda
 */ 
#include "lcd.h"
#include <avr/io.h>
#include <avr/sfr_defs.h>

#include <util/delay.h>
#include <util/twi.h>

#include <stdio.h>
#include <stdlib.h>

char val[2];

// at 8 Mhz
static void i2c_set_100kHz() {
	TWBR = 32;
}

static void i2c_set_400kHz() {
	TWBR = 2;
}

// NB: clearing TWINT starts next transmission
// TWI == I2C
// TWCR = TWI Control Register
// TWDR = TWI Data Register

// start master tranmssion
static void i2c_start() {
	// clear TWINT fla, send START, enable TWI unit
	TWCR = _BV(TWINT) | _BV(TWSTA) | _BV(TWEN);
	loop_until_bit_is_set(TWCR, TWINT);
	// NB: TWSTA must be cleared explicitly in the next operation
}

static void i2c_stop() {
	// clear TWINT flag, send STOP, enable TWI unit
	TWCR = _BV(TWINT) | _BV(TWSTO)| _BV(TWEN);
	loop_until_bit_is_clear(TWCR, TWSTO);
	// NB: TWSTO is cleared automatically
	// NB: TWINT is NOT set after STOP transmision .. 
}

// rw: TW_READ (1) or TW_WRITE(0)
static void i2c_set_address(uint8_t addr, uint8_t rw) {
	TWDR = (addr << 1) | rw;
	// clear TWINT flag, send STOP, enable TWI unit
	TWCR = _BV(TWINT) | _BV(TWEN);
	loop_until_bit_is_set(TWCR, TWINT);
}

static void setup() {
	lcd_init(); /* Initialization of LCD*/
	lcd_clear();
	i2c_set_100kHz();

	// uncomment if I2C modules don't come with pull-ups
	// DDRC &= ~_BV(DDC4); PORTC |= _BV(PORTC4);
	// DDRC &= ~_BV(DDC5); PORTC |= _BV(PORTC5);
}

static void probe_address(uint8_t i) 
{
	i2c_start();
	i2c_set_address(i, TW_WRITE);
	if ((TWSR & TW_STATUS_MASK) == TW_MT_SLA_ACK) 
		
		lcd_clear();
		lcd_write_word("Port:");
		lcd_write_word(itoa(i, val, 2));
		lcd_write_word(" ");
		_delay_ms(2000);
	i2c_stop();
}

static void scan() {
	// skipping reserved addresses
	for (uint32_t i = 8; i < 128; ++i)
		probe_address(i);
}


int main(void)
{
	setup();

	for(;;)	{
		scan();
	}


	while(1) {
		// lcd_clear();
		// //lcd_write_word("Ahoj Marku.     ");
		// lcd_write_word("ABCDEFGHIJKLMNOP");
		// _delay_ms(2000);
		// lcd_clear();
		// lcd_write_word("QRSTWXYZ12345678");
		// _delay_ms(2000);
	};
}

