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
	
	PCF_DateTime senddatetime;
	senddatetime.day = 8;
	senddatetime.month = 12;
	senddatetime.year = 2024;
	senddatetime.hour = 2;
	senddatetime.minute = 10;
	senddatetime.second = 11;
	PCF_SetDateTime(&senddatetime);
	
	InitMenu();
	sei();          // Global Interrupts
	
	while (1)
	{
	}
}



