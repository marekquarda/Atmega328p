/*
 * main.c
 *
 * Author : Hossam Elbahrawy
 */ 
#include "lcd.h"
#include "eeprom.h"


int main(void)
{
	lcd_init(); /* Initialization of LCD*/
	uint8_t run = 0;
	uint8_t err = 0;

	err = EEPROM_read(96, &run);
	uint8_t c = run+1;
	err = EEPROM_update(96,c);

	while(1) {
		lcd_clear();
		if (err != EEPROM_OK) {
			lcd_write_word("EEPROM Error");	
		} else {
			char text[] = "Start count: ";
			char ho[1];
			lcd_write_word(text);
			lcd_write_word(itoa(c, ho, 10));
			//lcd_write_character((char)c);
		}
		
//		lcd_write_word("ABCDEFGHIJKLMNOP");
		_delay_ms(2000);
//		lcd_clear();
//		lcd_write_word("QRSTWXYZ12345678");
		//lcd_write_word("Jak se mas?     ");
//		_delay_ms(2000);
		//lcd_write_word("ABCDEFGHIJKLMNOP");
		//lcd_goto_xy(1,0);
		//lcd_write_word("QRSTWXYZ12345678");
		
		// lcd_goto_xy(0,0);
		// lcd_write_word("90!@#$%&*)@#@##@");
		// lcd_goto_xy(1,0);
		// lcd_write_word("ElectronicWINGS@");	/* Write string on 1st line of LCD*/
		// //lcd_send_command(0xC0);		/* Go to 2nd line*/
		// lcd_goto_xy(0,0);
		// lcd_write_word("ElectronicWINGS@");	/* Write string on 2nd line*/
		// lcd_clear();
		// lcd_goto_xy(1,0);
		// lcd_write_word("8888888888888888");	/* Write string on 1st line of LCD*/
		// lcd_goto_xy(0,0);
		// //lcd_send_command(0xC0);		/* Go to 2nd line*/
		// lcd_write_word("8888888888888888");	/* Write string on 2nd line*/
	};
}

