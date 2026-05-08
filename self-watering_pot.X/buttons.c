#include "buttons.h"

volatile uint8_t button_pressed = 0;

void portc_interrupt_init(void)
{
    PORTC.DIR = 0x00;
    // button
    PORTC.PIN0CTRL = PORT_PULLUPEN_bm | PORT_ISC_FALLING_gc;
    // swimmer
    PORTD.PIN1CTRL = PORT_PULLUPEN_bm | PORT_ISC_INTDISABLE_gc;
}

void tcb_interrupt_init(void)
{
    TCA0.SINGLE.CTRLA = TCA_SINGLE_CLKSEL_DIV4_gc | TCA_SINGLE_ENABLE_bm;
    /* should be 10 ms */
    TCB0.CCMP = 50000;
    TCB0.INTCTRL = TCB_CAPT_bm;
    TCB0.CTRLA = TCB_CLKSEL_CLKTCA_gc;
}

ISR(PORTC_PORT_vect, ISR_BLOCK) {
    if (PORTC.INTFLAGS & PIN0_bm) {
        PORTC.INTFLAGS |= PIN0_bm;
    }

    TCB0.CTRLA |= TCB_ENABLE_bm;
}

ISR(TCB0_INT_vect, ISR_BLOCK) {
    TCB0.INTFLAGS |= TCB_CAPT_bm;
    TCB0.CTRLA &= ~TCB_ENABLE_bm;

    if (!(PORTC.IN & PIN0_bm)) {
        button_pressed = 1;
    }
}

int run_out_of_water(void)
{
    return !(!(PORTD.IN & PIN1_bm));
}
