
/*
 * LCD.c
 *
 * Author : Hossam Elbahrawy
 */ 
#include "lcd.h"


void lcd_init(void)
{	
	
	DATA_DDR |= (LCD_D7) | (LCD_D6) | (LCD_D5)| (LCD_D4) | (LCD_VCC);
	CTL_DDR |= (LCD_EN)|(LCD_RS)|(LCD_K);

	DATA_BUS |= (LCD_D7)|(LCD_D6)|(LCD_D5)|(LCD_D4)|(LCD_VCC);
	CTL_BUS|= (LCD_EN)|(LCD_RS)|(LCD_K);
	_delay_ms(1);
	CTL_BUS &=~(LCD_EN);
	 _delay_ms(1);
	
	lcd_send_command(LCD_FUNCTION_4BIT_2LINES); 
	_delay_ms(1);
	//lcd_send_command(LCD_DISP_ON);
	lcd_send_command(LCD_DISP_ON_CURSOR_BLINK);
	_delay_ms(1);
	lcd_send_command(0x80);
}

void lcd_send_command (uint8_t command)
{
	// high value
	DATA_BUS=((command&0b11110000)>>4); 
	CTL_BUS &=~(LCD_RS);
	CTL_BUS |=(LCD_EN);
	_delay_ms(1);
	CTL_BUS &=~(LCD_EN);
	_delay_ms(1);
	//low value
	DATA_BUS=((command&0b00001111));
	CTL_BUS |=(LCD_EN);
	_delay_ms(1);
	CTL_BUS &=~(LCD_EN);
	_delay_ms(1);

	
}
void lcd_write_word(char* word)
{
	int i=0;
	while(word[i]!='\0')
	{
		lcd_write_character(word[i]);
		i++;
	}
}
void lcd_write_character(char character)
{
	// high value
	DATA_BUS=((character & 0b11110000)>>4);
	CTL_BUS|=(LCD_RS);
	CTL_BUS |=(LCD_EN);
	_delay_ms(2);
	CTL_BUS &=~(LCD_EN);
	_delay_ms(2);
	// low value
	DATA_BUS=((character & 0b00001111));
	CTL_BUS |=(LCD_EN);
	_delay_ms(2);
	CTL_BUS &=~(LCD_EN);
	_delay_ms(2);
	
}
void lcd_clear(void)
{
	lcd_send_command(LCD_CMD_CLEAR_DISPLAY);
	_delay_ms(5);
}
void lcd_goto_xy (uint8_t line,uint8_t pos)				//line = 0 or 1
{
	lcd_send_command((0x80|(line<<6))+pos);
	_delay_us (50);
}