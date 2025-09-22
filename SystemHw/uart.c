#include <stdint.h>

#include "uart.h"
#include "stm32f407xx.h"

void uart_send_char(char c)
{
    while (!(USART1->SR & USART_SR_TXE)); // Wait until TXE is set
    USART1->DR = (uint8_t)c;              // Send the character
}

char uart_receive_char(void)
{
    while (!(USART1->SR & USART_SR_RXNE)); // Wait until RXNE is set
    return (char)USART1->DR;               // Read the received character
}