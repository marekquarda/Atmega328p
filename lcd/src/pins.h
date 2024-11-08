/*
 * pin_config.h
 *
 * Author : Hossam Elbahrawy
 */ 
#ifndef PIN_CONFIG_H_
#define PIN_CONFIG_H_

#include <avr/io.h>
#include <util/delay.h>

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
#define LCD_K           PD5  // 5
//#define	LCD_RW	    // GND
#define LCD_EN			PD6  // 6
#define	LCD_RS			PD7  // 7






#endif /* PIN_CONFIG_H_ */