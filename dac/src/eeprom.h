/*
 * eeprom.h
 *
 * Created: 2024-11-01 20:00:00
 *  Author: Marek Xara Quarda
 *
 */
#include <avr/io.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include <avr/interrupt.h>

#ifndef EEPROM_H_
#define EEPROM_H_

// Entire EEPROM size
#define EEPROM_SIZE 1023
// Addresses for values
#define CURRENT_ADDR 10   
#define VOLTAGE_ADDR 20    
#define DATE_DD_ADDR 30
#define DATE_MM_ADDR 40
#define DATE_YY_ADDR 50
#define TIME_HH_ADDR 60
#define TIME_MM_ADDR 70

enum{
    EEPROM_OK,
    EEPROM_WRITE_FAIL,
    EEPROM_INVALID_ADDR
};

uint8_t EEPROM_read(uint16_t uiAddress, uint8_t* data);
uint8_t EEPROM_write(uint16_t uiAddress, uint8_t* data);
uint8_t EEPROM_update(uint16_t uiAddress, uint8_t ucData);
uint8_t EEPROM_update_batch(uint16_t uiAdress, void *data, uint16_t len);
uint8_t EEPROM_read_batch(uint16_t uiAdress, void *data, uint16_t len);

#endif // EEPROM_H_