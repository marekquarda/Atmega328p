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
	PCF_Init(1);
	initInterruptSettings();
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
	
	InitMenu();
	
	while (1)
	{
		
	}
}



