#include "micromenu.h"
#include "lcd.h"
#include "clock.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "timer1.h"
#include "eeprom.h"

static bool time = false;
static uint16_t current = 0;
static uint16_t voltage = 0;
static bool once = false;

/** Time menu item select callback function */
static void Time_Select(void)
{
    viewTimeDate(SHOW_TIME);
}

/** Date menu item select callback function */
static void Date_Select(void)
{
    viewTimeDate(SHOW_TIME);
}

/** Voltage menu item select callback function */
static void Voltage_Select(void)
{
    viewTimeDate(SHOW_NONE);
    uint8_t err = 0;
    err = EEPROM_read_batch(VOLTAGE_ADDR, (void*) voltage,2);
    printValue(PRINT_VOLTAGE);
}

/** Current menu item select callback function */
static void Current_Select(void)
{
    viewTimeDate(SHOW_NONE);
    EEPROM_read_batch(CURRENT_ADDR, (void*) current, 2);
    printValue(PRINT_CURRENT);
}

/** Voltage Setting Up */
static void Voltage_Setting_Up(void)
{
    setVoltageVal(VOLTAGE_SET_UP);
}

/** Voltage Setting Down */
static void Voltage_Setting_Down(void)
{
    setVoltageVal(VOLTAGE_SET_DOWN);
}

/** Voltage Setting Up */
static void Current_Setting_Up(void)
{
    setCurrentVal(CURRENT_SET_UP);
}

/** Voltage Setting Down */
static void Current_Setting_Down(void)
{
    setCurrentVal(CURRENT_SET_DOWN);
}

/** Change Current value counter */
void setCurrentVal(ButtonSet value) {
    once = (once == true)?false:true;
    switch (value)
    {
    case CURRENT_SET_UP:
        if(once) {
            current++;
        }
        break;
    case CURRENT_SET_DOWN:
        if(once) {
            current= ((current--)==0)?0:current;
        }
        break;
    }
    // print value
    printValue(PRINT_CURRENT);
}

/** Change Voltage value counter */
void setVoltageVal(ButtonSet value) {
    once = (once == true)?false:true;
    switch (value)
    {
    case VOLTAGE_SET_UP:
        if(once) {
            voltage++;
        }
        break;
    case VOLTAGE_SET_DOWN:
        if(once) {
            voltage= ((voltage--)==0)?0:voltage;
        }
        break;
    }
    // Print value
    printValue(PRINT_VOLTAGE);
}

/** Print values (voltage, current) */
void printValue(PrintValues value)
 {
    LCDclr();
    char val[10];
    switch (value)
    {
    case PRINT_VOLTAGE:
        LCDstring("Voltage: ");
        if(voltage<10) {
            LCDstring("0.");
            LCDstring(itoa(voltage, val, 10));
        } else{
            uint8_t whole = voltage/10;
            uint8_t rest =  voltage%10;
            LCDstring(itoa(whole, val, 10));
            LCDsendChar('.');
            LCDstring(itoa(rest, val, 10));
        }
        break;

    case PRINT_CURRENT:
        LCDstring("Current: ");
        if(current<10) {
            LCDstring("0.");
            LCDstring(itoa(current, val, 10));
        } else{
            uint8_t whole = current/10;
            uint8_t rest =  current%10;
            LCDstring(itoa(whole, val, 10));
            LCDsendChar('.');
            LCDstring(itoa(rest, val, 10));
        }
        break;
    default:
        LCDstring("Unknown value");
        break;
    }
}

static void Current_Save() {
    LCDclr();
    EEPROM_update_batch(CURRENT_ADDR, (void*)current, 2);
    LCDstring("Current saved");
    //lcd_write_word("EEPROM Error");
}

static void Voltage_Save() {
    LCDclr();
    EEPROM_update_batch(VOLTAGE_ADDR, (void*) voltage,2);
    LCDstring("Voltage saved");
}


// Menu initialization
MENU_ITEM(Menu_1, Menu_2, Menu_3, NULL_MENU, NULL_MENU, Time_Select, NULL, "1");
MENU_ITEM(Menu_2, Menu_3, Menu_1, NULL_MENU, Menu_1_1, Voltage_Select,NULL,"2");
MENU_ITEM(Menu_3, Menu_1, Menu_2, NULL_MENU, Menu_2_1, Current_Select, NULL, "3");
//MENU_ITEM(Menu_4, Menu_1, NULL_MENU, NULL_MENU, NULL_MENU, Current_Select,Current_Enter, "4");

// Voltage SubMenu initialization
MENU_ITEM(Menu_1_1, Menu_1_2, Menu_1_1, Menu_SV, NULL_MENU, Voltage_Setting_Up, NULL, "1.1");
MENU_ITEM(Menu_1_2, Menu_1_2, Menu_1_1, Menu_SV, NULL_MENU, Voltage_Setting_Down, NULL, "1.2");

// Current SubMenu initialization
MENU_ITEM(Menu_2_1, Menu_2_2, Menu_2_1, Menu_SC, NULL_MENU, Current_Setting_Up, NULL, "2.1");
MENU_ITEM(Menu_2_2, Menu_2_2, Menu_2_1, Menu_SC, NULL_MENU, Current_Setting_Down, NULL, "2.2");

MENU_ITEM(Menu_SC, NULL_MENU, NULL_MENU, Menu_3, NULL_MENU, Current_Save, NULL,"3.0");
MENU_ITEM(Menu_SV, NULL_MENU, NULL_MENU, Menu_2, NULL_MENU, Voltage_Save, NULL, "3.0");

void InitMenu() {
    // Init menu
	Menu_Navigate(&Menu_1);
}



