/*
 * mcp4725.h
 *
 * Author : Marek Xara Quarda
 */ 
#ifndef MCP4725_H_
#define MCP4725_H_

#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>

#define DAC_GND_ADDRESS_WRITE        0xC0      // GND WRITE  
#define DAC_GND_ADDRESS_READ         0xC1      // GND READ
#define DAC_VCC_ADDRESS_WRITE        0xC2      // VCC WRITE
#define DAC_VCC_ADDRESS_READ         0xC3      // VCC READ

// i2c settings 
#define DAC_I2CINIT         0           // init i2c

// registers
#define DAC_WRITEDAC        0x40
#define DAC_WRITEDACEEPROM  0x60
#define DAC_READDAC         0x03

// set power down mode
#define DAC_NORMALMODE      0
#define DAC_POWERDOWN1K     1
#define DAC_POWERDOWN100K   100
#define DAC_POWERDOWN500K   500
//#define DAC_POWERDOWNMODE   DAC_POWERDOWN1K
#define DAC_POWERDOWNMODE   DAC_POWERDOWN1K

// functions 
extern void dac_init(unsigned char address, bool resetic);
extern void dac_setrawoutputfast(uint8_t address, uint16_t rawoutput);
extern void dac_setvoltagefast(uint8_t address, double voltage,double dacref);
extern void dac_settrawoutput(uint8_t address, uint16_t rawoutput, bool savetoeeprom);
extern void dac_setvoltage(uint8_t address, double voltage, double dacref, bool savetoeeprom);

#endif