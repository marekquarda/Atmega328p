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
#include "mcp4725.h"


int main(void)
{
	LCDinit(); /* Initialization of LCD*/
	LCDclr();
	initInterruptSettings();
	PCF_Init(1);
	timer1_Init();
	dac_init(DAC_GND_ADDRESS, true);
	//dac_init(DAC_VCC_ADDRESS, true);
	
	PCF_DateTime senddatetime;
	senddatetime.day = 8;
	senddatetime.month = 12;
	senddatetime.year = 2024;
	senddatetime.hour = 22;
	senddatetime.minute = 3;
	senddatetime.second = 10;
	PCF_SetDateTime(&senddatetime);
	
	InitMenu();
	sei();          // Global Interrupts

	// set dac default
	//dac_setvoltage(DAC_GND_ADDRESS, 1, 5, 1);
	//dac_setvoltage(DAC_VCC_ADDRESS, 2, 5, 1);

	while (1)
	{
	}
}



