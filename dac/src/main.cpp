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

	PCF_DateTime senddatetime;
	senddatetime.day = 10;
	senddatetime.month = 12;
	senddatetime.year = 2024;
	senddatetime.hour = 17;
	senddatetime.minute = 0;
	senddatetime.second = 10;

	PCF_SetDateTime(&senddatetime);
	dac_init(DAC_GND_ADDRESS_WRITE, false);
	dac_init(DAC_VCC_ADDRESS_WRITE, false);
	
	InitMenu();
	sei();          // Global Interrupts

	while (1)
	{
	}
}



 