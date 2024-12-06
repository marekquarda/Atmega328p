/*
 * pin_config.h
 *
 * Created: 2024-11-01 20:00:32
 * Author : Marek Xara Quarda
 */ 
#ifndef PIN_CONFIG_H_
#define PIN_CONFIG_H_

#include <avr/io.h>
#include <inttypes.h>
#include <util/delay.h>
#include <avr/pgmspace.h>

#define DATA_BUS	PORTB
#define CTL_BUS		PORTD
#define DATA_DDR	DDRB
#define CTL_DDR		DDRD

// define port B
#define LCD_D4			PB0  // 0
#define LCD_D5			PB1  // 1
#define LCD_D6			PB2  // 2 
#define LCD_D7			PB3  // 3
#define LCD_VCC         PB4  // 4
// define port D
#define PWR_C           PD3  // 3
#define LCD_K           PD5  // 5

#define INT_CLOCK       PC1  // 1

//#define	LCD_RW	    // GND
#define	LCD_RS			PD6  // 6
#define LCD_EN			PD7  // 7

#endif /* PIN_CONFIG_H_ */