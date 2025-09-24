/* 
 * File:   spi.h
 * Author: maxymsmal
 *
 * Created on September 22, 2025, 22:11 PM
 */
#ifndef SPI_H
#define SPI_H 
 
#include "stm32f407xx.h"

#include <stdint.h>
#include <stddef.h>

/*
 * Function: write_byte_spi
 * -------------------------
 * Sends a single byte of data over SPI.
 *
 * data: The byte of data to send.
 */
void spi_write_byte(uint8_t data);

/*
 * Function: write_data_spi
 * -------------------------
 * Sends multiple bytes of data over SPI.
 *
 * data: Pointer to the data buffer to send.
 * size: The number of bytes to send.
 */
void spi_write_data(uint8_t* data, size_t size);

/*
 * Function: read_byte_spi
 * ------------------------
 * Reads a single byte of data from SPI.
 *
 * returns: The byte of data read from SPI.
 */
uint8_t spi_read_byte(void);

/*
 * Function: read_data_spi
 * ------------------------
 * Reads multiple bytes of data from SPI.
 *
 * data: Pointer to the buffer to store the received data.
 * size: The number of bytes to read.
 */
void spi_read_data(uint8_t* data, size_t size);

#endif /* SPI_H */