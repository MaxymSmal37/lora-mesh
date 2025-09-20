/* 
 * File:   system_init.h
 * Author: maxymsmal
 *
 * Created on September 20, 2025, 2:01 PM
 */
#ifndef SYSTEM_INIT_H
#define SYSTEM_INIT_H

/**
 * @brief Initialize the clock system.
 */
void clock_init(void);

/**
 * @brief Initialize the timer system.
 */
void timer_init(void);

/**
 * @brief Initialize the GPIO system.
 */     
void gpio_init(void);

/**
 * @brief Initialize the UART system.
 */
void uart_init(void);

/**
 * @brief Initialize the I2C system.
 */
void i2c_init(void);

/**
 * @brief Initialize the SPI system.
 */
void spi_init(void);

/**
 * @brief Initialize the entire system.
 */
void sys_init(void);

/**
 * @brief Initialize the NVIC (Nested Vectored Interrupt Controller).
 */
void NVIC_init(void);

/**
 * @brief Initialize the entire system.
 */
void sys_init(void);

#endif // SYSTEM_INIT_H