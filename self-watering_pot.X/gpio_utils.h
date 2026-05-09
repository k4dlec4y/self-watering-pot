/* 
 * File:   gpio_utils.h
 * Author: k4dlec4y
 *
 * Created on May 8, 2026, 1:34 PM
 */

#ifndef GPIO_UTILS_H
#define	GPIO_UTILS_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <avr/interrupt.h>

extern volatile uint8_t button_pressed;

void button_init(void);

void swimmer_init(void);

int run_out_of_water(void);

#ifdef	__cplusplus
}
#endif

#endif	/* GPIO_UTILS_H */
