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
#define LCD_D4			0b00000001  // 0
#define LCD_D5			0b00000010  // 1
#define LCD_D6			0b00000100  // 2 
#define LCD_D7			0b00001000  // 3
#define LCD_EN			0b01000000  // 6
//#define	LCD_RW	    0b00010000  // 4  // GND
#define	LCD_RS			0b10000000  // 7
#define LCD_K           0b00100000  // 5
#define LCD_VCC         0x00010000  // 4




#endif /* PIN_CONFIG_H_ */