#include "micromenu.h"
#include "lcd.h"

/** Example menu item specific enter callback function, run when the associated menu item is entered. */
static void Level1Item1_Enter(void)
{
    LCDclr();
    LCDstring((uint8_t*) "ENTER 1",7);
}

/** Example menu item specific select callback function, run when the associated menu item is selected. */
static void Level1Item1_Select(void)
{
    LCDclr();
    LCDstring((uint8_t*) "SELECT 1",8);
}

static void Level1Item2_Enter(void)
{
    LCDclr();
    LCDstring((uint8_t*) "ENTER 2",7);
}

/** Example menu item specific select callback function, run when the associated menu item is selected. */
static void Level1Item2_Select(void)
{
    LCDclr();
    LCDstring((uint8_t*) "SELECT 2",8);
}

static void Level1Item3_Enter(void)
{
    LCDclr();
    LCDstring((uint8_t*) "ENTER 3",7);
}

/** Example menu item specific select callback function, run when the associated menu item is selected. */
static void Level1Item3_Select(void)
{
    LCDclr();
    LCDstring((uint8_t*) "SELECT 3",8);
}

// Menu initialization
MENU_ITEM(Menu_1, Menu_2, Menu_3, NULL_MENU, NULL_MENU, Level1Item1_Select, Level1Item1_Enter, "1");
MENU_ITEM(Menu_2, Menu_3, Menu_1, NULL_MENU, NULL_MENU, Level1Item2_Select, Level1Item2_Enter, "2");
MENU_ITEM(Menu_3, Menu_1, Menu_2, NULL_MENU, NULL_MENU, Level1Item3_Select, Level1Item3_Enter, "3");

// SubMenu initialization
MENU_ITEM(Menu_1_1, Menu_1_2, Menu_1_2, NULL_MENU, NULL_MENU, NULL, NULL, "1.1");
MENU_ITEM(Menu_1_2, Menu_1_1, Menu_1_1, NULL_MENU, NULL_MENU, NULL, NULL, "1.1");

void InitMenu() {
    // Init menu
	Menu_Navigate(&Menu_1);
}