
#ifndef UART_H
#define UART_H

#include "stm32f407xx.h"

/**
 * @brief Send a character via UART1.
 * 
 * @param c The character to send.
 */
void uart_send_char(char c);


char uart_receive_char(void);

#endif // UART_H