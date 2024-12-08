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

#define MIRROR_BYTE(x)	(x<<1&0x10)|(x>>1&0x08)|(x<<3&0x20)|(x>>3&0x04)|(x<<5&0x40)|(x>>5&0x02)|(x<<7&0x80)|(x>>7&0x01)

/* set entry mode: display shift on/off, dec/inc cursor move direction */
#define LCD_ENTRY_DEC            0x04   /* display shift off, dec cursor move dir */
#define LCD_ENTRY_DEC_SHIFT      0x05   /* display shift on,  dec cursor move dir */
#define LCD_ENTRY_INC_           0x06   /* display shift off, inc cursor move dir */
#define LCD_ENTRY_INC_SHIFT      0x07   /* display shift on,  inc cursor move dir */

/* display on/off, cursor on/off, blinking char at cursor position */
#define LCD_DISP_OFF             0x08   /* display off                            */
#define LCD_DISP_ON              0x0C   /* display on, cursor off                 */
#define LCD_DISP_ON_BLINK        0x0D   /* display on, cursor off, blink char     */
#define LCD_DISP_ON_CURSOR       0x0E   /* display on, cursor on                  */
#define LCD_DISP_ON_CURSOR_BLINK 0x0F   /* display on, cursor on, blink char      */

/* move cursor/shift display */
#define LCD_MOVE_CURSOR_LEFT     0x10   /* move cursor left  (decrement)          */
#define LCD_MOVE_CURSOR_RIGHT    0x14   /* move cursor right (increment)          */
#define LCD_MOVE_DISP_LEFT       0x18   /* shift display left                     */
#define LCD_MOVE_DISP_RIGHT      0x1C   /* shift display right                    */ 

/* Function set: set interface data length and number of display lines */
#define LCD_FUNCTION_4BIT_1LINE  0x20   /* 4-bit interface, single line, 5x7 dots */
#define LCD_FUNCTION_4BIT_2LINES 0x28   /* 4-bit interface, dual line,   5x7 dots */
#define LCD_FUNCTION_8BIT_1LINE  0x30   /* 8-bit interface, single line, 5x7 dots */
#define LCD_FUNCTION_8BIT_2LINES 0x38   /* 8-bit interface, dual line,   5x7 dots */

#define	LCD_ENABLE	CTL_BUS|=(1<<LCD_EN)	
#define	LCD_DISABLE	CTL_BUS&=~(1<<LCD_EN)
#define RS_ENABLE   CTL_BUS|=(1<<LCD_RS)	
#define RS_DISABLE  CTL_BUS&=~(1<<LCD_RS)
#define VCC_DISABLE DATA_BUS|=(1<<LCD_VCC)	
#define VCC_ENABLE  DATA_BUS&=~(1<<LCD_VCC)
#define K_ENABLE 	CTL_BUS|=(1<<LCD_K)	
#define K_DISABLE   CTL_BUS&=~(1<<LCD_K)

#define PWR_ENABLE  CTL_BUS|=(1<<PWR_C)	
#define PWR_DISABLE CTL_BUS&=~(1<<PWR_C)

//functions prototype
void lcd_init(void);
void lcd_send_command (unsigned char cmnd);
void lcd_write_character(unsigned char data);
void lcd_write_word(char* str);
void lcd_clear(void);
void lcd_set_courser(uint8_t,uint8_t);
void lcd_goto_xy (uint8_t , uint8_t );



#endif /* LCD_H_ */