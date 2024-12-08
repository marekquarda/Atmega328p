/*
 * mcp4725.cpp
 *
 * Author : Marek Xara Quarda
 */ 

#include "mcp4725.h"
#include "i2cmaster.h"
#include "lcd.h"

/**
 * Initialize
 */
void dac_init(unsigned char address, bool resetic) 
{    
    #if DAC_I2CINIT == 1
        i2c_init();
        _delay_us(10);
    #endif

    // set power down mode (disabled)
    i2c_start(address);
    #if DAC_POWERDOWNMODE == DAC_POWERDOWN1K
        i2c_write(0b01000010);
    #elif DAC_POWERDOWNMODE == DAC_POWERDOWN100K
        i2c_write(0b01000100);
    #elif DAC_POWERDOWNMODE == DAC_POWERDOWN500K
        i2c_write(0b01000110);
    #endif
    if(resetic) {
        i2c_write(0b00000000);
        i2c_write(0b00000000);
    }
    i2c_stop();
}

/**
 * Set the value to output fast mode
 */
void dac_setrawoutputfast(uint8_t address, uint16_t rawoutput)
{
    // write raw output value to register
    i2c_start(address);
    i2c_write((uint8_t)(rawoutput>>8));
    i2c_write((uint8_t)(rawoutput));
    i2c_stop();
}

/**
 * Set a voltage value to ouput fast mode 
 */
void dac_setvoltagefast(uint8_t address, double voltage, double dacref)
{
    uint16_t rawoutput = 0;

    // get the raw ouput
    rawoutput = voltage*4096/dacref;
    if(rawoutput > 4095)
        rawoutput = 4095;

    // write to chip
    dac_setrawoutputfast(address, rawoutput);
}

/**
 * Set the raw value to output 
 */
void dac_settrawoutput(uint8_t address, uint16_t rawoutput, bool savetoeeprom)
{
    // write raw output value to register
    uint8_t err = i2c_start(address);
    if (err) LCDstring("Error DAC");
    if(savetoeeprom) {
        i2c_write(DAC_WRITEDACEEPROM);
    } else {
        i2c_write(DAC_WRITEDAC);
    }
    //i2c_write((uint8_t)(rawoutput>>4));
    i2c_write(rawoutput/16);
    i2c_write((rawoutput%16)<<14);
    //rawoutput = (rawoutput<<12);
    //i2c_write((uint8_t)(rawoutput>>8));
    i2c_stop();
}

/**
 * Set a voltage to output
 */
void dac_setvoltage(uint8_t address, double voltage, double dacref, bool savetoeeprom) 
{
    uint16_t rawoutput = 0;

    //get the raw output
    rawoutput = voltage*4096/dacref;
    if(rawoutput > 4095);
        rawoutput = 4095;

    // write to chip
    dac_settrawoutput(address, rawoutput,savetoeeprom);
}