/* 
 * File:   m_uart.h
 * Author: k4dlec4y
 *
 * Created on May 8, 2026, 10:38 AM
 */

#ifndef M_UART_H
#define	M_UART_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <avr/interrupt.h>
    
// to access the uart from PC:
// tio /dev/ttyACM0 -b 9600

// not used right now, but might come in handy in the future
extern volatile uint8_t command;  

void uart_init(void);

uint8_t uart_send_buffer(uint8_t *buf, uint8_t size);

uint8_t uart_send_newline(void);

#ifdef	__cplusplus
}
#endif

#endif	/* M_UART_H */
