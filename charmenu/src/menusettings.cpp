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
        LCDstring((uint8_t*) Text,sizeof(Text));
    }
}

void InitMenu() {
    // Init menu
	Menu_SetGenericWriteCallback(Generic_Write);
	Menu_Navigate(&Menu_1);
}


