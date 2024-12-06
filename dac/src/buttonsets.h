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

enum ButtonValues 
{
    BTN_NONE,
    BTN_LONG_UP,
    BTN_LONG_SET,
    BTN_SHORT_UP,
    BTN_SHORT_SET
};

enum MenuPosition 
{
    DEFAULT_POS,
   	SETING_MODE,
};



void initInterruptSettings(void);

// Menu settings
enum ButtonValues GetButtonPress(void);
enum MenuPosition GetMenuPosition(void);
void SetMenuPosition(MenuPosition);
void ChooseItem(void);


#endif // SETTINGS_H_
