/*
 * clock.h
 *
 * Created: 2024-11-01 20:00:00
 *  Author: Marek Xara Quarda
 */ 
 #include "lcdpins.h"

#ifndef CLOCK_H_
#define CLOCK_H_


#define PCF8563_READ_ADDR				0xA3
#define PCF8563_WRITE_ADDR				0xA2

#define PCF_ALARM_FLAG					(1<<3)
#define PCF_TIMER_FLAG					(1<<2)
#define PCF_ALARM_INTERRUPT_ENABLE		(1<<1)
#define PCF_TIMER_INTERRUPT_ENABLE		(1<<0)

#define PCF_CLKOUT_32768HZ				0b10000000
#define PCF_CLKOUT_1024HZ				0b10000001
#define PCF_CLKOUT_32HZ					0b10000010
#define PCF_CLKOUT_1HZ					0b10000011
#define PCF_CLKOUT_DISABLED				0b00000000

#define PCF_TIMER_4096HZ				0b10000000
#define PCF_TIMER_64HZ					0b10000001
#define PCF_TIMER_1HZ					0b10000010
#define PCF_TIMER_1_60HZ				0b10000011
#define PCF_TIMER_DISABLED				0b00000011

#define PCF_DISABLE_ALARM				80

#define I2C_CONFIG_F_SCL				100000
#define I2C_CONFIG_DDR					DDRC
#define I2C_CONFIG_PORT					PORTC
#define I2C_CONFIG_SDA					PC4
#define I2C_CONFIG_SCL					PC5
#define TW_SCL_PIN						PORTC5
#define TW_SDA_PIN						PORTC4


#define INT_ENABLE   I2C_CONFIG_PORT|=(1<<INT_CLOCK)	
#define INT_DISABLE  I2C_CONFIG_PORT&=~(1<<INT_CLOCK)

typedef struct {
	uint8_t minute;
	uint8_t hour;
	uint8_t day;
	uint8_t weekday;
} PCF_Alarm;

typedef struct {
	uint8_t second;
	uint8_t minute;
	uint8_t hour;
	uint8_t day;
	uint8_t weekday;
	uint8_t month;
	uint16_t year;
} PCF_DateTime;


void PCF_Write(uint8_t addr, uint8_t *data, uint8_t count);
void PCF_Read(uint8_t addr, uint8_t *data, uint8_t count);

void PCF_Init(uint8_t mode);
uint8_t PCF_GetAndClearFlags(void);

void PCF_SetClockOut(uint8_t mode);

void PCF_SetTimer(uint8_t mode, uint8_t count);
uint8_t PCF_GetTimer(void);

uint8_t PCF_SetAlarm(PCF_Alarm *alarm);
uint8_t PCF_GetAlarm(PCF_Alarm *alarm);

uint8_t PCF_SetDateTime(PCF_DateTime *dateTime);
uint8_t PCF_GetDateTime(PCF_DateTime *dateTime);


#endif /* CLOCK_H_ */