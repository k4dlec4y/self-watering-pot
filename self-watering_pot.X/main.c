#include <avr/io.h>
#include <avr/interrupt.h>
#include "m_uart.h"

uint8_t button_string[8] = {'b', 'u', 't', 't', 'o', 'n', ':', ' '};
uint8_t newline[2] = {'\r', '\n'};

volatile uint8_t button = 0;

int main(void) {

    cli(); //disable interrupts global

    // set clock prescaler to 0: CPU runs at 20MHz
    CPU_CCP = CCP_IOREG_gc;
    CLKCTRL.MCLKCTRLB = 0x00;

    PORTC.DIR = 0x00;

    uart_init();

    sei(); //enable interrupts global

    while (1) {
        uint8_t cur_command = command;
        if (cur_command != 0) {
            command = 0;
            if (cur_command == 'a') {
                uart_send_buffer(button_string, sizeof(button_string));
                uint8_t status = '0' + button;
                uart_send_buffer(&status, 1);
                uart_send_buffer(newline, sizeof(newline));
            }
        }
    }
}
