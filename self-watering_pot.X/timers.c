#include "timers.h"
#include <assert.h>
#include <stdio.h>
#include <inttypes.h>
#include "m_uart.h"
#include "gpio_utils.h"
#include "moisture_adc.h"
#include "config.h"

volatile uint8_t status = 0;
volatile uint64_t time_since_last_watering = 0;
volatile uint64_t seconds_from_start = 0;
volatile uint16_t status_timer = 0;
volatile uint16_t pump_timer = 0;
volatile int16_t lockout_timer = 0;
volatile uint8_t pump_active = 0;

void rtc_timer_init(void)
{
    while (RTC.PITSTATUS & RTC_CTRLABUSY_bm);

    RTC.CLKSEL = RTC_CLKSEL_INT32K_gc;
    RTC.PITINTCTRL = RTC_PI_bm;
    RTC.PITCTRLA = RTC_PERIOD_CYC32768_gc | RTC_PITEN_bm;
}

ISR(RTC_PIT_vect, ISR_BLOCK)
{
    RTC.PITINTFLAGS = RTC_PI_bm;

    seconds_from_start++;

    status_timer++;
    if (status_timer >= STATUS_PERIOD) {
        status_timer = 0;
        status = 1; 
    }

    if (pump_active) {
        pump_timer++;
        if (pump_timer >= PUMP_ACTIVE_PERIOD || run_out_of_water())
            pump_off();
    }

    if (lockout_timer > 0) {
        lockout_timer--;
    }
}

void pump_init(void)
{
    PORTE.DIRSET = PIN0_bm;
}

void pump_on(void)
{
    if (lockout_timer <= 0 && !pump_active && !run_out_of_water()) {
        PORTE.OUTSET = PIN0_bm;
        pump_active = 1;
        pump_timer = 0;
    }
}

void pump_off(void)
{
    PORTE.OUTCLR = PIN0_bm;
    pump_active = 0;
    pump_timer = 0;
    time_since_last_watering = seconds_from_start;

    lockout_timer = PUMP_LOCKOUT_PERIOD; 
}

#define MESSAGE_SIZE 128
uint8_t message[MESSAGE_SIZE];

void send_status(void)
{
    uint8_t sreg = SREG;
    cli();
    uint64_t water_time = pump_active
                          ? 0
                          : seconds_from_start - time_since_last_watering;
    uint8_t pump = pump_active;
    uint16_t moisture = moisture_value;
    uint8_t water_status = run_out_of_water();
    SREG = sreg;

    int written = snprintf(message, MESSAGE_SIZE,
        "[INFO] Time since last watering: %" PRIu64 "h, %" PRIu64 "m, %" PRIu64 " s\r\n",
        water_time / 3600, water_time / 60 % 60, water_time % 60);
    assert(written > 0);
    uart_send_buffer(message, written);

    written = snprintf(message, MESSAGE_SIZE,
        "[INFO] Moisture: %d%% -- Reservoir: %s -- Pump: %s\r\n",
        moisture * 100 / MOISTURE_MAX, water_status ? "EMPTY" : "OK",
        pump ? "ON" : "OFF");
    assert(written > 0);
    uart_send_buffer(message, written);
}
