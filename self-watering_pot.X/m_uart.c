#include "m_uart.h"

volatile uint8_t command = 0;

#define SIZE 255
uint8_t buffer[SIZE];
volatile uint8_t head = 0;
volatile uint8_t tail = 0;
volatile uint8_t empty_size = SIZE;   

ISR(USART3_RXC_vect, ISR_BLOCK) {
    command = USART3.RXDATAL;
}

ISR(USART3_DRE_vect, ISR_BLOCK) {
    if (tail != head) {
        USART3.TXDATAL = buffer[tail];
        tail = (tail + 1) % SIZE;
        empty_size++;
    } else {
        USART3.CTRLA &= ~USART_DREIE_bm;
    }
}

void uart_init(void)
{
    USART3.BAUD = 8333;
    USART3.CTRLC = USART_CMODE_ASYNCHRONOUS_gc |
            USART_PMODE_DISABLED_gc |
            USART_CHSIZE_8BIT_gc |
            USART_SBMODE_1BIT_gc;
    USART3.CTRLA = USART_RXCIE_bm;
    PORTB.DIR = 0x01;
    USART3.CTRLB = USART_RXEN_bm | USART_TXEN_bm;
}

uint8_t uart_send_buffer(uint8_t *buf, uint8_t size)
{
    uint8_t sreg = SREG;
    cli(); 

    if (size > empty_size) {
        return 0;
    }
    empty_size -= size;
    for (uint16_t i = 0; i < size; ++i) {
        buffer[head] = buf[i];
        head = (head + 1) % SIZE;
    }
    USART3.CTRLA |= USART_DREIE_bm;

    SREG = sreg;
    return 1;
}
