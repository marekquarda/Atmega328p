/*
 * main.c
 *
 * Created: 2024-11-01 20:00:32
 * Author : Marek Xara Quarda
 */ 
#include "lcd.h"
#include <avr/io.h>
#include <util/delay.h>
#include "twi_timer.h"

#define RTC_READ_ADDR (0xA3)

int main(void)
{
	lcd_init(); /* Initialization of LCD*/
	lcd_clear();
	twi_init();	// 100khz 
	uint8_t rtc_data[7];
	uint8_t err = twi_read(RTC_READ_ADDR, 0x08,rtc_data,1);
	// if (err != TWI_OK) {
	// 	lcd_write_word("Error communication");
	// } else {
		lcd_write_word("Year: ");
		lcd_write_character(rtc_data[0]);
		 //+ rtc_data[0]);
//	}
	

	//lcd_clear();
	//lcd_write_word("ElectronicWINGS");	/* Write string on 1st line of LCD*/
	//lcd_send_command(0xC0);		/* Go to 2nd line*/
	//lcd_write_word("Hello World");	/* Write string on 2nd line*/
// 	while(1) {
// 		lcd_clear();
// 		//lcd_write_word("Ahoj Marku.     ");
// 		lcd_write_word("ABCDEFGHIJKLMNOP");
// 		_delay_ms(2000);
// 		lcd_clear();
// 		lcd_write_word("QRSTWXYZ12345678");
// 		//lcd_write_word("Jak se mas?     ");
// 		_delay_ms(2000);
// 		//lcd_write_word("ABCDEFGHIJKLMNOP");
// 		//lcd_goto_xy(1,0);
// 		//lcd_write_word("QRSTWXYZ12345678");
		
// 		// lcd_goto_xy(0,0);
// 		// lcd_write_word("90!@#$%&*)@#@##@");
// 		// lcd_goto_xy(1,0);
// 		// lcd_write_word("ElectronicWINGS@");	/* Write string on 1st line of LCD*/
// 		// //lcd_send_command(0xC0);		/* Go to 2nd line*/
// 		// lcd_goto_xy(0,0);
// 		// lcd_write_word("ElectronicWINGS@");	/* Write string on 2nd line*/
// 		// lcd_clear();
// 		// lcd_goto_xy(1,0);
// 		// lcd_write_word("8888888888888888");	/* Write string on 1st line of LCD*/
// 		// lcd_goto_xy(0,0);
// 		// //lcd_send_command(0xC0);		/* Go to 2nd line*/
// 		// lcd_write_word("8888888888888888");	/* Write string on 2nd line*/
// 	};
}

