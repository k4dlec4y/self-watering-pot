#include <avr/io.h>
#include <avr/interrupt.h>
#include "m_uart.h"
#include "gpio_utils.h"
#include "moisture_adc.h"
#include "timers.h"
#include "config.h"

int main(void)
{
    cli(); //disable interrupts global

    // set clock prescaler to 0: CPU runs at 20MHz
    CPU_CCP = CCP_IOREG_gc;
    CLKCTRL.MCLKCTRLB = 0x00;

    uart_init();
    button_init();
    swimmer_init();
    pump_init();
    moisture_adc_init();
    rtc_timer_init();

    sei(); //enable interrupts global

    while (1) {
        if (button_pressed) {
            button_pressed = 0;
            pump_on();
        }
        if (moisture_value < MOISTURE_THRESHOLD) {
            pump_on();
        }
        if (status) {
            status = 0;
            send_status();
        }
    }
}
