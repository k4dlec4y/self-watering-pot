#include <avr/io.h>
#include <avr/interrupt.h>
#include "m_uart.h"
#include "buttons.h"

uint8_t button_string[8] = {'b', 'u', 't', 't', 'o', 'n', ':', ' '};
uint8_t newline[2] = {'\r', '\n'};

int main(void) {

    cli(); //disable interrupts global

    // set clock prescaler to 0: CPU runs at 20MHz
    CPU_CCP = CCP_IOREG_gc;
    CLKCTRL.MCLKCTRLB = 0x00;

    uart_init();
    portc_interrupt_init();
    tcb_interrupt_init();

    sei(); //enable interrupts global

    while (1) {
        if (button_pressed) {
            button_pressed = 0;
            uart_send_buffer(button_string, sizeof(button_string));
            uint8_t status = '0' + !(PORTC.IN & 0b1);
            uart_send_buffer(&status, 1);
            uart_send_buffer(newline, sizeof(newline));
        }
    }
}
