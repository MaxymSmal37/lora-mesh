/* 
 * File:   sx1278_lora.h
 * Author: maxymsmal
 *
 * Created on September 22, 2025, 22:20 PM
 */
#ifndef SX1278_LORA_H
#define SX1278_LORA_H

#include <stdint.h>
#include <stddef.h>

#define SLEEP_MODE_MASK ~((1 << 2) | (1 << 1) | (1 << 0)) 
#define STANDBY_R_MASK ~((1 << 2) | (1 << 1)) 
#define STANDBY_S_MASK (1 << 0) 
#define TX_MODE_R_MASK ~(1 << 2)
#define TX_MODE_S_MASK ((1 << 1) | (1 << 0))
#define CONTINUOUS_RX_R_MASK ~(1 << 1)  
#define CONTINUOUS_RX_S_MASK ((1 << 2) | (1 << 0))
#define SINGLE_RX_R_MASK ~(1 << 0)
#define SINGLE_RX_S_MASK ((1 << 2) | (1 << 1))

#define DELAY_FOR_SET_MODE 5

enum SX1278_LORA_Mode{
    LORA_MODE_SLEEP = 0,
    LORA_MODE_STANDBY,
    LORA_MODE_TX,
    LORA_MODE_RX_CONTINUOUS,
    LORA_MODE_RX_SINGLE
};

/*
* Function: sx1278_lora_init
* --------------------------
* Initializes the SX1278 LoRa module.
*/
void sx1278_lora_init(void);

/*
* Function: sx1278_lora_write_byte
* --------------------------------
* Writes a byte of data to a specified register address in the SX1278 LoRa module.
* address: The register address to write to.
* data: The byte of data to write.
*/
void sx1278_lora_write_byte(uint8_t address, uint8_t data);

/*
* Function: sx1278_lora_read_byte
* -------------------------------
* Reads a byte of data from a specified register address in the SX1278 LoRa module.
* address: The register address to read from.
* returns: The byte of data read from the register.
*/
uint8_t sx1278_lora_read_byte(uint8_t address);

/*
* Function: sx1278_lora_send_data
* --------------------------------
* Sends multiple bytes of data to a specified register address in the SX1278 LoRa module.
* address: The register address to write to.
* data: Pointer to the data buffer to send.
* size: The number of bytes to send.
*/
void sx1278_lora_send_data(uint8_t address, uint8_t* data, size_t size);

/*
* Function: sx1278_lora_read_data
* --------------------------------
* Reads multiple bytes of data from a specified register address in the SX1278 LoRa module.
* address: The register address to read from.
* buffer: Pointer to the buffer to store the read data.
* size: The number of bytes to read.
*/
void sx1278_lora_read_data(uint8_t address, uint8_t* buffer, size_t size);

/*
* Function: sx1278_lora_set_mode
* --------------------------------                      
* Sets the operating mode of the SX1278 LoRa module.
* mode: The desired operating mode (LORA_MODE_SLEEP, LORA_MODE_STANDBY,
*       LORA_MODE_TX, LORA_MODE_RX_CONTINUOUS, LORA_MODE_RX_SINGLE).
*/
uint8_t sx1278_lora_set_mode(uint8_t mode);

/*
* Function: sx1278_lora_set_channel
* ---------------------------------
* Sets the operating frequency channel of the SX1278 LoRa module.
* frequency: The desired frequency in MHz (e.g., 433, 868, 915).
*/
void sx1278_lora_set_channel(uint32_t frequency);

/*
* Function: sx1278_lora_tx
* -------------------------
* Transmits a byte of data using the SX1278 LoRa module.
* byte: The byte of data to transmit.
*/
void sx1278_lora_tx(uint8_t byte);

/*
* Function: sx1278_lora_rx
* -------------------------
* Receives a byte of data using the SX1278 LoRa module.
* byte: Pointer to the variable to store the received byte.
*/
void sx1278_lora_rx(uint8_t* byte);

void sx1278_lora_handle_TIMER_ms(void);

#endif // SX1278_LORA_H