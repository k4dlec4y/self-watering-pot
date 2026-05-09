/* 
 * File:   moisture_adc.h
 * Author: k4dlec4y
 *
 * Created on May 8, 2026, 1:52 PM
 */

#ifndef MOISTURE_ADC_H
#define	MOISTURE_ADC_H

#ifdef	__cplusplus
extern "C" {
#endif

extern volatile uint16_t moisture_value;

void moisture_adc_init(void);

#ifdef	__cplusplus
}
#endif

#endif	/* MOISTURE_ADC_H */

