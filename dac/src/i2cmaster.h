/*
 * i2cmaster.h
 *
 * Author : Marek Xara Quarda
 */ 
#ifndef I2CMASTER_H_
#define I2CMASTER_H_

#include <avr/io.h>
#include <inttypes.h>
#include "compat/twi.h"

// data direction
#define I2C_READ        1
#define I2C_WRITE       0

// functions
extern void i2c_init(void);
extern void i2c_stop(void);
extern uint8_t i2c_start(uint8_t addr);
extern uint8_t i2c_rep_start(uint8_t addr);
extern void i2c_start_wait(uint8_t addr);
extern uint8_t i2c_write(uint8_t data);
extern uint8_t i2c_readAck(void);
extern uint8_t i2c_readNak(void);
extern uint8_t i2c_read(uint8_t ack);

#define i2c_read(ack) ?i2c_readAck() : i2c_readNak();

#endif