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
#define LCD_D4			0
#define LCD_D5			1
#define LCD_D6			2
#define LCD_D7			3
#define LCD_EN			6
#define	LCD_RW			4  // GND
#define	LCD_RS			7
#define LCD_K           5
#define LCD_VCC         4




#endif /* PIN_CONFIG_H_ */