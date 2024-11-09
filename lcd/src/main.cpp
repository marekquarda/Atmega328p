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
	lcd_init(); /* Initialization of LCD*/
	//lcd_clear();
	//lcd_write_word("ElectronicWINGS");	/* Write string on 1st line of LCD*/
	//lcd_send_command(0xC0);		/* Go to 2nd line*/
	//lcd_write_word("Hello World");	/* Write string on 2nd line*/
	while(1) {
		lcd_clear();
		lcd_write_word("ElectronicWINGS@");	/* Write string on 1st line of LCD*/
		lcd_send_command(0xC0);		/* Go to 2nd line*/
		lcd_write_word("ElectronicWINGS@");	/* Write string on 2nd line*/
		lcd_clear();
		lcd_write_word("8888888888888888");	/* Write string on 1st line of LCD*/
		//lcd_send_command(0xC0);		/* Go to 2nd line*/
		lcd_goto_xy(1,0);
		lcd_write_word("8888888888888888");	/* Write string on 2nd line*/
	};
}

