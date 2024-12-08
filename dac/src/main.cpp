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
#include "test.h"


int main(void)
{
	LCDinit(); /* Initialization of LCD*/
	LCDclr();
	initInterruptSettings();
	PCF_Init(1);
	timer1_Init();
	//dac_init(DAC_GND_ADDRESS, true);
	//dac_init(DAC_VCC_ADDRESS, true);

	PCF_DateTime senddatetime;
	senddatetime.day = 8;
	senddatetime.month = 12;
	senddatetime.year = 2024;
	senddatetime.hour = 22;
	senddatetime.minute = 3;
	senddatetime.second = 10;
	PCF_SetDateTime(&senddatetime);
	dac_init(DAC_GND_ADDRESS_WRITE, true);
	dac_init(DAC_VCC_ADDRESS_WRITE, true);
	//dac_setvoltagefast(DAC_GND_ADDRESS_WRITE, 5, 5);
	//dac_setvoltagefast(DAC_VCC_ADDRESS_WRITE, 5, 5);
	
	InitMenu();
	sei();          // Global Interrupts

	// set dac default
	
	for(;;) {
		for(uint8_t i =0; i < 256; i++) {
			uint8_t sinval = sine256[i];
			dac_setvoltagefast(DAC_GND_ADDRESS_WRITE, sinval, 255);
			_delay_ms(10);
			//dac_setvoltagefast(DAC_VCC_ADDRESS_WRITE, sinval, 255);	
		}
	}

	while (1)
	{
		// dac_setvoltage(DAC_GND_ADDRESS, 3, 5, 0);
		// dac_setvoltage(DAC_VCC_ADDRESS, 2, 5, 0);
		// _delay_ms(100);
	}
}



 