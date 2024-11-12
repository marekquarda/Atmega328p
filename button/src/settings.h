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
void shortButtonUp(void);
void longButtonUp(void);
void shortButtonSet(void);
void longButtonSet(void);

#endif // SETTINGS_H_
