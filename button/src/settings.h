/*
 * settings.h
 *
 * Created: 2024-11-01 20:00:32
 * Author : Marek Xara Quarda
 */ 
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>


#ifndef SETTINGS_H_
#define SETTINGS_H_

#define BTN_DEBOUCE 20 //ms

void initInterruptSettings(void);

#endif // SETTINGS_H_
