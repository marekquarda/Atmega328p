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
#define LCD_D4			0x01
#define LCD_D5			0x02
#define LCD_D6			0x03
#define LCD_D7			0x04
#define LCD_EN			0x06
#define	LCD_RW			0x04  // GND
#define	LCD_RS			0x07
#define LCD_K           0x05
#define LCD_VCC         0x04




#endif /* PIN_CONFIG_H_ */