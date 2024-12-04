#include "micromenu.h"
#include "lcd.h"
#include "clock.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

static bool time = false;
static uint8_t current = 0;
static uint8_t voltage = 0;
PreviousBtn preposition = PREV_BTN_NONE;

/** Time menu item select callback function */
static void Time_Select(void)
{
    LCDclr();
    PCF_DateTime datetime;
    LCDstring((uint8_t*)"Time:", 5);
    time = true;
    // while (time)
    // {
       	uint8_t err = PCF_GetDateTime(&datetime);
 		char ho[4];
 		char min[4];
 		char sec[4];
		LCDstring((uint8_t*)(itoa(datetime.hour, ho, 10)), 2);
		LCDsendChar(':');
		LCDstring((uint8_t*)(itoa(datetime.minute, min, 10)), 2);
		LCDsendChar(':');
		LCDstring((uint8_t*)(itoa(datetime.second, sec, 10)), 2);
        // move to back
        LCDcursorLeft(8);
  //      _delay_ms(900);
    //     time = false;
    // }

}

static void Time_Enter(void)
{
    LCDclr();
    LCDstring((uint8_t*)"Time Ent",8);
}


/** Date menu item select callback function */
static void Date_Select(void)
{
    LCDclr();
    PCF_DateTime datetime;
    LCDstring((uint8_t*)"Date:", 5);
    time = true;
    // while (time)
    // {
       	uint8_t err = PCF_GetDateTime(&datetime);
 		char ho[4];
 		char min[4];
 		char sec[4];
		LCDstring((uint8_t*)(itoa(datetime.day, ho, 10)), 2);
		LCDsendChar('/');
		LCDstring((uint8_t*)(itoa(datetime.month, min, 10)), 2);
		LCDsendChar('/');
		LCDstring((uint8_t*)(itoa(datetime.year, sec, 10)), 4);
        // move to back
        LCDcursorLeft(10);
//        _delay_ms(900);
    //     time = false;
}

static void Date_Enter(void)
{
    LCDclr();
    LCDstring((uint8_t*)"Date Ent",8);
}

/** Voltage menu item select callback function */
static void Voltage_Select(void)
{
    LCDclr();
    char val[10];
    LCDstring("Voltage: ");
    LCDstring(itoa(voltage, val, 10));
}

// static void Voltage_Enter(void)
// {
//     LCDclr();
//     LCDstring((uint8_t*)"Voltage Ent",11);
// }

/** Current menu item select callback function */
static void Current_Select(void)
{
    LCDclr();
    char val[10];
    LCDstring("Current: ");
    LCDstring(itoa(current, val, 10));
}

// static void Current_Enter(void)
// {
//     LCDclr();
//     LCDstring((uint8_t*)"Current Ent",11);
// }

/** Voltage Setting Up */
static void Voltage_Setting_Up(void)
{
    setVoltageVal(VOLTAGE_SET_UP);
    preposition = PREV_BTN_UP;
}

/** Voltage Setting Down */
static void Voltage_Setting_Down(void)
{
    setVoltageVal(VOLTAGE_SET_SET);
    preposition = PREV_BTN_SET;
}

/** Voltage Setting Up */
static void Current_Setting_Up(void)
{
    setCurrentVal(CURRENT_SET_UP);
    preposition = PREV_BTN_UP;
}

/** Voltage Setting Down */
static void Current_Setting_Down(void)
{
    setCurrentVal(CURRENT_SET_SET);
    preposition = PREV_BTN_SET;
}

/** Change Current value counter */
void setCurrentVal(ButtonSet value) {
    switch (GetPreviousBtn())
    {
    case PREV_BTN_UP:
        switch (value)
        {
        case CURRENT_SET_UP:
            current++;
            break;
        case CURRENT_SET_SET:
            current= ((current--)==0)?0:current;
            break;
        }
        break;
    case PREV_BTN_SET:
        switch (value)
        {
        case CURRENT_SET_UP:
            current= ((current--)==0)?0:current;
            break;
        case CURRENT_SET_SET:
            current++;
            break;
        }
        break;
    default:
        break;
    }
    // print value
    LCDclr();
    char val[10];
    LCDstring("Current: ");
    LCDstring(itoa(current, val, 10));
}

/** Change Voltage value counter */
void setVoltageVal(ButtonSet value) {
    switch (GetPreviousBtn())
    {
    case PREV_BTN_UP:
        switch (value)
        {
        case VOLTAGE_SET_UP:
            voltage++;
            break;
        case VOLTAGE_SET_SET:
            voltage= ((voltage--)==0)?0:voltage;
            break;
        }
        break;
    case PREV_BTN_SET:
        switch (value)
        {
        case VOLTAGE_SET_UP:
            voltage= ((voltage--)==0)?0:voltage;
            break;
        case VOLTAGE_SET_SET:
            voltage++;
            break;
        }
    default:
        break;
    }
    // Print value
    LCDclr();
    char val[10];
    LCDstring("Voltage: ");
    LCDstring(itoa(voltage, val, 10));
}


// Menu initialization
MENU_ITEM(Menu_1, Menu_2, Menu_3, NULL_MENU, NULL_MENU, Time_Select, NULL, "1");
MENU_ITEM(Menu_2, Menu_3, Menu_1, NULL_MENU, Menu_1_1, Voltage_Select,NULL,"2");
MENU_ITEM(Menu_3, Menu_1, Menu_2, NULL_MENU, Menu_2_1, Current_Select, NULL, "3");
//MENU_ITEM(Menu_4, Menu_1, NULL_MENU, NULL_MENU, NULL_MENU, Current_Select,Current_Enter, "4");

// Voltage SubMenu initialization
MENU_ITEM(Menu_1_1, Menu_1_1, Menu_1_2, Menu_2, NULL_MENU, Voltage_Setting_Up, NULL, "1.1");
MENU_ITEM(Menu_1_2, Menu_1_1, Menu_1_2, Menu_2, NULL_MENU, Voltage_Setting_Down, NULL, "1.2");

// Current SubMenu initialization
MENU_ITEM(Menu_2_1, Menu_2_1, Menu_2_2, Menu_3, NULL_MENU, Current_Setting_Up, NULL, "2.1");
MENU_ITEM(Menu_2_2, Menu_2_1, Menu_2_2, Menu_3, NULL_MENU, Current_Setting_Down, NULL, "2.2");

void InitMenu() {
    // Init menu
	Menu_Navigate(&Menu_1);
}

// Return previous touch
PreviousBtn GetPreviousBtn() {
    return preposition;
}