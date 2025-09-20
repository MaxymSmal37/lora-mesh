/* 
 * File:   i2c.h
 * Author: maxymsmal
 *
 * Created on September 20, 2025, 2:01 PM
 */
#ifndef I2C_H
#define I2C_H

#include <stdint.h>

#define I2C_WRITE_MODE 0    
#define I2C_READ_MODE 1

/**
 * @brief Open the I2C1 peripheral.
 */
void I2C1_Open(void);

/**
 * @brief Start the I2C1 communication.
 */
void I2C1_Start(void);

/**
 * @brief Put the I2C1 peripheral in idle state.
 */
void I2C1_Idle(void);

/**
 * @brief Get the acknowledgment status from the I2C1 peripheral.
 * 
 * @return uint8_t ACK status (0: ACK received, 1: NACK received)
 */
uint8_t I2C1_getAck(void);

/**
 * @brief Send a byte of data via I2C1.
 * 
 * @param data The byte of data to send.
 */
void I2C1_SendData(uint8_t data);

/**
 * @brief Send the address and direction (read/write) to the I2C1 peripheral.
 * 
 * @param address The 7-bit address of the I2C device.
 * @param direction The direction of communication (I2C_WRITE_MODE or I2C_READ_MODE).
 */
void I2C1_Address(uint8_t address, uint8_t direction);

/**
 * @brief Read a byte of data from the I2C1 peripheral.
 * 
 * @param data Pointer to store the received byte of data.
 */
void I2C1_Read(uint8_t* data);

/**
 * @brief Stop the I2C1 communication.
 */
void I2C1_Stop(void);

/**
 * @brief Close the I2C1 peripheral.
 */
void I2C1_Close(void);

#endif // I2C_H