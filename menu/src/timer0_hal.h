/*
 * timer0_hal.h
 *
 * Created: 2024-11-01 20:00:32
 * Author : Marek Xara Quarda
 */ 
 #ifndef TIMER0_HAL_H
 #define TIMER0_HAL_H

 #include <stdint.h>
 #include <avr/io.h>
 #include <avr/interrupt.h>

 void timer0_init(void);
 uint32_t millis(void);
 uint8_t millis_end(uint32_t start_time, uint32_t delay_time);

 #endif 