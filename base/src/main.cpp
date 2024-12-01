/*
 * main.c
 *
 * Created: 2024-11-01 20:00:32
 * Author : Marek Xara Quarda
 */ 
#include "lcd.h"
#include <avr/io.h>
#include <util/delay.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "clock.h"
#include "buttonsets.h"
#include "micromenu.h"


int main(void)
{
	LCDinit(); /* Initialization of LCD*/
	LCDclr();
	initInterruptSettings();
	PCF_Init(1);
	
	//charmenu = new_CharMenu(charmenu);

	//twi_init();	// 100khz 
	//uint8_t rtc_data[7];
	PCF_DateTime senddatetime;
	senddatetime.day = 12;
	senddatetime.month = 11;
	senddatetime.year = 2024;
	senddatetime.hour = 14;
	senddatetime.minute = 50;
	senddatetime.second = 30;
//	senddatetime.
	PCF_SetDateTime(&senddatetime);
	
	//InitMenu();
	
	while (1)
	{
		PCF_DateTime datetime;
		uint8_t err = PCF_GetDateTime(&datetime);
		LCDclr();
//		lcd_write_word("Time: ");
		//memset(print_buffer, 0, sizeof(print_buffer));
		char ho[4];
		char min[4];
		char sec[4];
		//itoa(datetime.day, str, 1);
		//lcd_write_word(sprintf(print_buffer,"\r20%.2f/%.2f/%.2f", datetime.year, datetime.month, datetime.day));
		LCDstring((uint8_t*)"Time: ", 6);
		//lcd_write_word("Time: ");
		//LCDstring((uint8_t*)(itoa(datetime.hour, ho, 10), 2);
		LCDsendChar((uint8_t)datetime.hour);
		LCDsendChar(':');
		//LCDstring((uint8_t*)':',);
		LCDsendChar((uint8_t)datetime.minute);
		LCDsendChar(':');
		LCDsendChar((uint8_t)datetime.second);
		//lcd_write_character(' ');
		_delay_ms(2000);
		//lcd_goto_xy(1,0);
		// LCDclr();
		// lcd_write_word("Date: ");
		// lcd_write_word(itoa(datetime.day, sec, 10));
		// lcd_write_character('/');
		// lcd_write_word(itoa(datetime.month, sec, 10));
		// lcd_write_character('/');
		// lcd_write_word(itoa(datetime.year, sec, 10));
		// _delay_ms(1000);
	}
}



