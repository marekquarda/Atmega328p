/*
 * timer1.h
 *
 * Created: 2024-11-01 20:00:32
 * Author : Marek Xara Quarda
 */ 
#ifndef TIMER1_H_
#define TIMER1_H_

#include <avr/io.h>
#include <avr/interrupt.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "clock.h"
#include "lcd.h"

enum dateTime {
    SHOW_TIME,
    SHOW_DATE,
    SHOW_NONE
};

void show(void);
void timer1_Init(void);
void viewTimeDate(dateTime);

#endif