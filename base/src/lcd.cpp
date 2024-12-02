
/*
 * LCD.c
 *
 * Created: 2024-11-01 20:00:32
 * Author : Marek Xara Quarda
 */ 
#include "lcd.h"



void LCDinit(void)
{	
	DATA_DDR = (1<<LCD_VCC) | (1<<LCD_D7) | (1<<LCD_D6) | (1<<LCD_D5)| (1<<LCD_D4);
	CTL_DDR = (1<<LCD_EN) | (1<<LCD_RS) | (1<<LCD_K);// | (1<<PWR_C);

	DATA_BUS = (0<<LCD_D7) | (0<<LCD_D6) | (0<<LCD_D5) | (0<<LCD_D4);
	CTL_BUS = (1<<LCD_EN) | (0<<LCD_RS);

	_delay_ms(1);
	K_ENABLE;
	VCC_ENABLE;
	LCD_DISABLE;
	//PWR_DISABLE;

	_delay_ms(1);	
	LCDsendCommand(LCD_CMD_CURSOR_HOME);			/* send for 4 bit initialization of LCD  */
	_delay_ms(1);	
	//lcd_send_command(LCD_FUNCTION_4BIT_2LINES);     /* Use 2 line and initialize 5*7 matrix in (4-bit mode)*/
	LCDsendCommand(LCD_FUNCTION_4BIT_1LINE);
	_delay_ms(1);	
	LCDsendCommand(LCD_DISP_ON);    				/* Display on cursor off*/
	_delay_ms(1);	
	LCDsendCommand(LCD_ENTRY_INC_);		    	/* Increment cursor (shift cursor to right)*/
	_delay_ms(1);	
	//lcd_send_command(LCD_ENTRY_INC_SHIFT);     	/* Increment cursor (shift cursor to right)*/
	LCDsendCommand(LCD_CMD_CLEAR_DISPLAY);      	/* Clear display screen*/
	_delay_ms(1);
	//lcd_send_command(0x80);							/* Cursor 1st row 0th position */
}

void LCDsendCommand(uint8_t cmnd)
{
	// High value
	DATA_BUS=((DATA_BUS & 0xF0) | ((cmnd & 0xF0)>>4)); 
	RS_DISABLE;
	LCD_ENABLE;
	_delay_ms(1);
	LCD_DISABLE;
	_delay_ms(1);
	//low value
	DATA_BUS=((DATA_BUS & 0xF0) | (cmnd & 0x0F));
	LCD_ENABLE;
	_delay_ms(1);
	LCD_DISABLE;
	_delay_ms(2);
}

void LCDsendChar(char data)
{
	// high value
	DATA_BUS=((DATA_BUS & 0xF0) | ((data & 0xF0)>>4)); 
	RS_ENABLE;
	LCD_ENABLE;
	_delay_ms(1);
	LCD_DISABLE;
	_delay_ms(1);
	// low value
	DATA_BUS=((DATA_BUS & 0xF0) | (data & 0x0F));
	LCD_ENABLE;
	_delay_ms(1);
	LCD_DISABLE;
	_delay_ms(1);
}

void LCDclr(void)
{
	LCDsendCommand(LCD_CMD_CLEAR_DISPLAY); 	/* Clear display */
}

void LCDhome(void) 	
{
	LCDsendCommand(LCD_CMD_CURSOR_HOME);	/* LCD cursor home */
}

void LCDstring(char* string) {
	int i;
	for(i=0;string[i]!=0;i++)		/* Send each char of string till the NULL */
	{
		LCDsendChar(string[i]);
	}
}

void LCDstring(uint8_t* data, uint8_t nBytes) // Outputs string to LCD
{
	register uint8_t i;
	// check to make sure we have a good pointer
	if (!data) return;
	// print data
	for(i = 0; i< nBytes; i++) {
		LCDsendChar(data[i]);
	}
}

void LCDGotoXY (uint8_t line,uint8_t pos)				//line = 0 or 1
{
	// if (line == 0 && pos<16)
	// 	LCDsendCommand((pos & 0x0F) | 0x80);	/* Command of first row and required position<16 */
	// else if (line == 1 && pos<16)
	// 	LCDsendCommand((pos & 0x0F) | 0xC0);	/* Command of first row and required position<16 */
	// cursor position to DDRAM mapping
	register uint8_t DDRAMAddr;
	// remap lines into proper order
	switch (pos)
	{
	case 0: DDRAMAddr = LCD_LINE0_DDRAMADDR+line;
		break;
	case 1: DDRAMAddr = LCD_LINE1_DDRAMADDR+line;
		break;
	case 2: DDRAMAddr = LCD_LINE2_DDRAMADDR+line;
		break;
	case 3: DDRAMAddr = LCD_LINE3_DDRAMADDR+line;
		break;
	default:
		DDRAMAddr = LCD_LINE0_DDRAMADDR+line;
	}
	// set data address
	LCDsendCommand(1<<LCD_DDRAM | DDRAMAddr);
}

//Copies string from flash memory to LCD at x y position
//const uint8_t welcomeln1[] PROGMEM="AVR LCD DEMO\0";
//CopyStringtoLCD(welcomeln1, 3, 1);	
void CopyStringtoLCD(const uint8_t *FlashLoc, uint8_t x, uint8_t y)
{
	uint8_t i;
	LCDGotoXY(x,y);
	for (i=0;(uint8_t)pgm_read_byte(&FlashLoc[i]);i++) 
	{
		LCDsendChar((uint8_t)pgm_read_byte(&FlashLoc[i]));
	}
}	

void LCDdefinechar(const uint8_t *pc, uint8_t char_code) 
{
	uint8_t a, pcc;
	uint16_t i;
	a = (char_code <<3) | 0x40;
	for (i=0;i<8;i++) {
		pcc = pgm_read_byte(&pc[i]);
		LCDsendCommand(a++);
		LCDsendChar(pcc);
	}
}

void LCDshiftLeft(uint8_t n)	// Scroll n of characters left
{
	for (uint8_t i=0;i<n;i++) {
		LCDsendCommand(LCD_MOVE_DISP_LEFT);
	}
}

void LCDshiftRight(uint8_t n) 
{
	for (uint8_t i=0;i<n;i++) {
		LCDsendCommand(LCD_MOVE_DISP_RIGHT);
	}
}

void LCDcursorOn(void) 
{
	LCDsendCommand(LCD_DISP_ON_CURSOR);
}

void LCDcursorOnBlink(void)
{
	LCDsendCommand(LCD_DISP_ON_CURSOR_BLINK);
}

void LCDcursorOFF(void) 
{
	LCDsendCommand(LCD_DISP_ON);	// must be display on only
}

void LCDblank(void) 
{
	LCDsendCommand(LCD_DISP_OFF);	// must be display off
}

void LCDvisible(void)
{
	LCDsendCommand(LCD_DISP_ON);	// Shows LCD
}

void LCDcursorLeft(uint8_t n) 		// Moves cursor by n positions left
{
	for(uint8_t i=0;i<n;i++) 
	{
		LCDsendCommand(LCD_MOVE_CURSOR_LEFT);
	}
}

void LCDcursorRight(uint8_t n)		// Moves cursor by n position right
{
	for(uint8_t i=0;i<n;i++)
	{
		LCDsendCommand(LCD_MOVE_CURSOR_RIGHT);
	}
}

void LCDprogressBar(uint8_t progress, uint8_t maxprogress, uint8_t length)
{
	uint8_t i;
	uint16_t pixelprogress;
	uint8_t c;
	// draw a progress bar displaying (progress / maxprogress)
	// starting from the current cursor position
	// with a total length of "length" characters
	// ***note, LCD chars 0-5 must be programmed as the bar characters
	// char 0 = empty ... char 5 = full

	// total pixel length of bargraph equals length*PROGRESSPIXELS_PER_CHAR;
	// pixel length of bar itself is
	pixelprogress = ((progress*(length*PROGRESSPIXELS_PER_CHAR))/maxprogress);

	// print exactly "length" characters
	for (i=0;i<length;i++) {
		// check if this is a full block, or partial or empty
		// (u16) cast is needed to avoid sign comparison warning
		if( ((i*(uint16_t)PROGRESSPIXELS_PER_CHAR)+5) > pixelprogress )
		{
			// this is a partial or empty block
			if( ((i*(uint16_t)PROGRESSPIXELS_PER_CHAR)) > pixelprogress )
			{
				// this is an empty block
				// use space character?
				c = 0;
			}
			else
			{
				// this is a partial block
				c = pixelprogress % PROGRESSPIXELS_PER_CHAR;
			}
		}
		else
		{
			// this is a full block
			c = 5;
		}
		// write character to display
		LCDsendChar(c);
	}
}