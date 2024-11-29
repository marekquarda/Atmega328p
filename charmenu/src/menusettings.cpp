#include "micromenu.h"
#include "lcd.h"

// Menu initialization
MENU_ITEM(Menu_1, Menu_2, Menu_3, NULL_MENU, NULL_MENU, NULL, NULL, "1");
MENU_ITEM(Menu_2, Menu_3, Menu_1, NULL_MENU, NULL_MENU, NULL, NULL, "2");
MENU_ITEM(Menu_3, Menu_1, Menu_2, NULL_MENU, NULL_MENU, NULL, NULL, "3");

// SubMenu initialization
MENU_ITEM(Menu_1_1, Menu_1_2, Menu_1_2, NULL_MENU, NULL_MENU, NULL, NULL, "1.1");
MENU_ITEM(Menu_1_2, Menu_1_1, Menu_1_1, NULL_MENU, NULL_MENU, NULL, NULL, "1.1");


static void Generic_Write(const char* Text) 
{
    if(Text) {
        LCDclr();
        LCDstring((uint8_t*)"GENERIC:", 8);
        LCDstring((uint8_t*)Text,10);
    }
}

void InitMenu() {
    // Init menu
	Menu_SetGenericWriteCallback(Generic_Write);
	Menu_Navigate(&Menu_1);
}

/** Example menu item specific enter callback function, run when the associated menu item is entered. */
static void Level1Item1_Enter(void)
{
	//puts("ENTER");
    LCDclr();
    LCDstring((uint8_t*) "ENTER 1",7);
}

/** Example menu item specific select callback function, run when the associated menu item is selected. */
static void Level1Item1_Select(void)
{
	//puts("SELECT");
    LCDclr();
    LCDstring((uint8_t*) "SELECT 1",8);
}

static void Level1Item2_Enter(void)
{
	//puts("ENTER");
    LCDclr();
    LCDstring((uint8_t*) "ENTER 2",7);
}

/** Example menu item specific select callback function, run when the associated menu item is selected. */
static void Level1Item2_Select(void)
{
	//puts("SELECT");
    LCDclr();
    LCDstring((uint8_t*) "SELECT 2",8);
}

static void Level1Item3_Enter(void)
{
	//puts("ENTER");
    LCDclr();
    LCDstring((uint8_t*) "ENTER 3",7);
}

/** Example menu item specific select callback function, run when the associated menu item is selected. */
static void Level1Item3_Select(void)
{
	//puts("SELECT");
    LCDclr();
    LCDstring((uint8_t*) "SELECT 3",8);
}


