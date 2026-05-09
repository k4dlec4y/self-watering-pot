/* 
 * File:   status.h
 * Author: k4dlec4y
 *
 * Created on May 8, 2026, 9:30 PM
 */

#ifndef TIMERS_H
#define	TIMERS_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <avr/interrupt.h>

extern volatile uint8_t status;

void rtc_timer_init(void);

void pump_init(void);

void pump_on(void);

void pump_off(void);

void send_status(void);

#ifdef	__cplusplus
}
#endif

#endif	/* TIMERS_H */

