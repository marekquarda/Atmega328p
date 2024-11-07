/*
 * main.c
 *
 * Author : Hossam Elbahrawy
 */ 
#include "lcd.h"
#include <avr/io.h>
#include <util/delay.h>




int main(void)
{
	
	lcd_init();
	
	// lcd_write_character('h');
	// lcd_write_character('o');
	// lcd_write_character('j');
	//lcd_write_word("Hello, World!");
	lcd_goto_xy(13,0);
	//lcd_write_character(1);
	//lcd_write_word("LCD is working");
 
}

