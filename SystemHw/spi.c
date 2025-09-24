#include "spi.h"
#include <stdint.h>
#include "stddef.h"

void spi_write_byte(uint8_t data)
{
  while (!(SPI1->SR & SPI_SR_TXE)) {}
  *((volatile uint8_t *)&SPI1->DR) = data;
}

void spi_write_data(uint8_t *data, size_t size)
{
  for (size_t i = 0; i < size; i++)
  {
    spi_write_byte(data[i]);
  }
}

uint8_t spi_read_byte(void)
{
  while (!(SPI1->SR & SPI_SR_RXNE)) {}
  return *((volatile uint8_t *)&SPI1->DR);
}

void spi_read_data(uint8_t *data, size_t size)
{
  for (size_t i = 0; i < size; i++)
  {
    data[i] = spi_read_byte();
  }
}
