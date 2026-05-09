#include <avr/io.h>
#include <avr/interrupt.h>
#include "m_uart.h"
#include "buttons.h"
#include "humidity_adc.h"
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
    humidity_adc_init();
    timers_init();

    sei(); //enable interrupts global

    while (1) {
        if ((button_pressed || humidity_value < HUMIDITY_THRESHOLD)
            && !run_out_of_water()) {
            start_pump();
        }
        if (status) {
            status = 0;
            send_status();
        }
    }
}
