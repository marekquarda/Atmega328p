/*
 * LCD.h
 *
 * Author : Hossam Elbahrawy
 */ 
#ifndef LCD_H_
#define LCD_H_

#include "pins.h"

#define LCD_CMD_CLEAR_DISPLAY	          0x01
#define LCD_CMD_CURSOR_HOME		          0x02

// Display control
#define LCD_CMD_DISPLAY_OFF                0x08
#define LCD_CMD_DISPLAY_NO_CURSOR          0x0c
#define LCD_CMD_DISPLAY_CURSOR_NO_BLINK    0x0E
#define LCD_CMD_DISPLAY_CURSOR_BLINK       0x0F

/* Function set: set interface data length and number of display lines */
#define LCD_FUNCTION_4BIT_1LINE  0x20   /* 4-bit interface, single line, 5x7 dots */
#define LCD_FUNCTION_4BIT_2LINES 0x28   /* 4-bit interface, dual line,   5x7 dots */
#define LCD_FUNCTION_8BIT_1LINE  0x30   /* 8-bit interface, single line, 5x7 dots */
#define LCD_FUNCTION_8BIT_2LINES 0x38   /* 8-bit interface, dual line,   5x7 dots */

//functions prototype
void lcd_init(void);
void lcd_send_command (uint8_t );
void lcd_write_character(char);
void lcd_write_word(char*);
void lcd_clear(void);
void lcd_set_courser(uint8_t,uint8_t);
void lcd_goto_xy (uint8_t , uint8_t );



#endif /* LCD_H_ */