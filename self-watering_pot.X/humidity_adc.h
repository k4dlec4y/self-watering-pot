/* 
 * File:   humidity_adc.h
 * Author: k4dlec4y
 *
 * Created on May 8, 2026, 1:52 PM
 */

#ifndef HUMIDITY_ADC_H
#define	HUMIDITY_ADC_H

#ifdef	__cplusplus
extern "C" {
#endif

extern volatile uint16_t humidity_value;

void humidity_adc_init(void);

#ifdef	__cplusplus
}
#endif

#endif	/* HUMIDITY_ADC_H */

