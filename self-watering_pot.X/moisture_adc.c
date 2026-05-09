#include <avr/interrupt.h>
#include "config.h"

volatile uint16_t moisture_value = MOISTURE_MAX;

ISR(ADC0_RESRDY_vect, ISR_BLOCK)
{
    // sensor returns the highest voltage if dry
    moisture_value = MOISTURE_MAX - ADC0.RES;
}

void moisture_adc_init(void)
{
    /* turn off digital */
    PORTD.PIN0CTRL = PORT_ISC_INPUT_DISABLE_gc;

    ADC0.CTRLA = ADC_ENABLE_bm | ADC_FREERUN_bm;
    ADC0.CTRLC = ADC_PRESC_DIV16_gc | ADC_REFSEL_VDDREF_gc;
    ADC0.MUXPOS = ADC_MUXPOS_AIN0_gc;
    ADC0.INTCTRL = ADC_RESRDY_bm;
    ADC0.COMMAND = ADC_STCONV_bm;
}
