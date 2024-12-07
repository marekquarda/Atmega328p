/*
 * timer1.cpp
 *
 * Created: 2024-11-01 20:00:32
 * Author : Marek Xara Quarda
 */ 
#include "timer1.h"

dateTime showtimedate;

ISR(TIMER1_OVF_vect) {
    // reset timer
    TCNT1 = 65535 - (F_CPU/1024);
    show();
}

void timer1_Init() {
    TCNT1 = 65535 - (F_CPU/1024);
    //sets the prescaler to 1024
    // 8M/1024 = 7812,5Hz
    TCCR1B = (1 << CS10) |(1 << CS12);
    TCCR1A = 0;
    TIMSK1 = (1 << TOIE1);
}

void viewTimeDate(dateTime show) {
    showtimedate = show;
}

void show() {
    PCF_DateTime datetime;
    char ho[4];
 	char min[4];
 	char sec[4];
    
    switch (showtimedate)
    {
    case SHOW_TIME:
        LCDclr();
        PCF_GetDateTime(&datetime);
        LCDstring((uint8_t*)"Time:", 5);
        if(datetime.hour < 10) {
            LCDsendChar('0');
            LCDstring((uint8_t*)(itoa(datetime.hour, ho, 10)), 1);
        } else {
            LCDstring((uint8_t*)(itoa(datetime.hour, ho, 10)), 2);
        }
		LCDsendChar(':');
        if(datetime.minute < 10) {
            LCDsendChar('0');
            LCDstring((uint8_t*)(itoa(datetime.minute, min, 10)), 1);
        } else{
            LCDstring((uint8_t*)(itoa(datetime.minute, min, 10)), 2);
        }
		LCDsendChar(':');
        if(datetime.second < 10) {
            LCDsendChar('0');
            LCDstring((uint8_t*)(itoa(datetime.second, sec, 10)), 1);
        } else {
            LCDstring((uint8_t*)(itoa(datetime.second, sec, 10)), 2);
        }
        break;
    
    case SHOW_DATE:
        LCDclr();
        PCF_GetDateTime(&datetime);
        LCDstring((uint8_t*)"Date:", 5);
        if (datetime.day < 10) {
            LCDsendChar('0');
            LCDstring((uint8_t*)(itoa(datetime.day, ho, 10)), 1);
        } else {
            LCDstring((uint8_t*)(itoa(datetime.day, ho, 10)), 2);
        }
		LCDsendChar('/');
        if (datetime.month < 10) {
            LCDsendChar('0');
            LCDstring((uint8_t*)(itoa(datetime.month, min, 10)), 1);
        } else {
            LCDstring((uint8_t*)(itoa(datetime.month, min, 10)), 2);                
        }
		LCDsendChar('/');
		LCDstring((uint8_t*)(itoa(datetime.year, sec, 10)), 4);
        break;

    case SHOW_NONE:
        break;

    default:
        break;
    }
}




