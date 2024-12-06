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
#include "timer1.h"
#include "micromenu.h"


int main(void)
{
	LCDinit(); /* Initialization of LCD*/
	LCDclr();
	initInterruptSettings();
	PCF_Init(1);
	timer1_Init();
	
	//charmenu = new_CharMenu(charmenu);

	//twi_init();	// 100khz 
	//uint8_t rtc_data[7];
	PCF_DateTime senddatetime;
	senddatetime.day = 4;
	senddatetime.month = 12;
	senddatetime.year = 2024;
	senddatetime.hour = 23;
	senddatetime.minute = 00;
	senddatetime.second = 30;
//	senddatetime.
	PCF_SetDateTime(&senddatetime);
	
	InitMenu();
	sei();          // Global Interrupts
	
	while (1)
	{

	}
}



