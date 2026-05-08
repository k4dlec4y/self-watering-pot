#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <assert.h>
#include "m_uart.h"
#include "buttons.h"
#include "humidity_adc.h"

#define HUMIDITY_MESSAGE_SIZE 64
uint8_t humidity_message[HUMIDITY_MESSAGE_SIZE];

int main(void) {

    cli(); //disable interrupts global

    // set clock prescaler to 0: CPU runs at 20MHz
    CPU_CCP = CCP_IOREG_gc;
    CLKCTRL.MCLKCTRLB = 0x00;

    uart_init();
    portc_interrupt_init();
    tcb_interrupt_init();
    humidity_adc_init();

    sei(); //enable interrupts global

    while (1) {
        if (button_pressed) {
            button_pressed = 0;

            uint8_t sreg = SREG;
            cli();
            uint16_t value = humidity_value;
            SREG = sreg;

            int written = snprintf(humidity_message, HUMIDITY_MESSAGE_SIZE,
                "Humidity: %u\r\n", value);
            assert(written > 0);

            uart_send_buffer(humidity_message, written);
        }
    }
}
