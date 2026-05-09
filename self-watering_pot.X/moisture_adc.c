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
    /* PORTDPIN0 = AIN0 = POT2*/
    PORTD.PIN0CTRL = 0x4;
    /* 0 = 10 bit, 1 = FREERUN, 1 = ENABLE */
    ADC0.CTRLA |= 0b011;
    ADC0.CTRLC = ADC_PRESC_DIV16_gc | ADC_REFSEL_VDDREF_gc;
    /* PIN SELECTION (AIN0) */
    ADC0.MUXPOS = 0x00;
    ADC0.INTCTRL = 1;
    /* SAMPLE */
    ADC0.COMMAND = 0b1;
}
