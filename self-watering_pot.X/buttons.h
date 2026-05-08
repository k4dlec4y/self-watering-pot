/* 
 * File:   buttons.h
 * Author: k4dlec4y
 *
 * Created on May 8, 2026, 1:34 PM
 */

#ifndef BUTTONS_H
#define	BUTTONS_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <avr/interrupt.h>

extern volatile uint8_t button_pressed;

void portc_interrupt_init(void);

void tcb_interrupt_init(void);

#ifdef	__cplusplus
}
#endif

#endif	/* BUTTONS_H */
