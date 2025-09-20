#include "stm32f407xx.h"
#include "i2c.h"

void I2C1_Open(void)
{
    I2C1->CR1 |= I2C_CR1_PE; // Enable the peripheral
}

void I2C1_Start()
{
    I2C1->CR1 |= (1<<8); // Generate the START condition
    while (!(I2C1->SR1 & (1<<0))); // Wait until SB is set
}

void I2C1_Idle()
{
    while (!(I2C1->SR1 & (1<<0))); // Wait until SB is set
}

uint8_t I2C1_getAck(void)
{
    return (I2C1->SR1 & (1<<10)) != 0; // Return the ACK bit status
}

uint8_t I2C1_getAckstatBit()
{
    return (I2C1->SR1 & (1<<10)) != 0; // Return the NACKF bit status
}
void I2C1_SendData(uint8_t data)
{
    I2C1->DR = data;
    while (!(I2C1->SR1 & (1<<7))); // Wait until TXE is set
}

void I2C1_Address(uint8_t address, uint8_t direction)
{
    I2C1->DR = (address << 1) | direction;
    while (!(I2C1->SR1 & (1<<1))); // Wait until ADDR is set
    (void)I2C1->SR2;               // Clear the ADDR flag by reading SR2
}

void I2C1_Read(uint8_t* data)
{
    while (!(I2C1->SR1 & (1<<6))); // Wait until RXNE is set
    *data = I2C1->DR;
}

void I2C1_Stop(void)
{
    I2C1->CR1 |= (1<<9);   // Generate the STOP condition
    while (I2C1->SR2 & (1<<1)); // Wait until BUSY is reset
}

void I2C1_Close(void)
{
    I2C1->CR1 &= ~I2C_CR1_PE; // Disable the peripheral
}