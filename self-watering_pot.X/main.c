#include <avr/io.h>
#include <avr/interrupt.h>
#include "m_uart.h"
#include "buttons.h"
#include "moisture_adc.h"
#include "timers.h"
#include "config.h"

int main(void) {

    cli(); //disable interrupts global

    // set clock prescaler to 0: CPU runs at 20MHz
    CPU_CCP = CCP_IOREG_gc;
    CLKCTRL.MCLKCTRLB = 0x00;

    uart_init();
    portc_interrupt_init();
    tcb_interrupt_init();
    moisture_adc_init();
    timers_init();

    sei(); //enable interrupts global

    while (1) {
        if ((button_pressed || moisture_value < MOISTURE_THRESHOLD)
            && !run_out_of_water()) {
            start_pump();
        }
        if (status) {
            status = 0;
            send_status();
        }
    }
}
