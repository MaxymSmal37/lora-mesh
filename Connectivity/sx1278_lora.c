#include <stdint.h>
#include "sx1278_lora.h"
#include "spi.h"
#include "stm32f407xx.h"

volatile uint16_t mode_delay_ms = 0;

void sx1278_lora_write_byte(uint8_t address, uint8_t data)
{
  GPIOA->ODR &= ~(1 << 4); // Set NSS low to select the device
  address |= 0x80;         // Set MSB for write operation
  spi_write_byte(address); // Send address
  spi_write_byte(data);    // Send data
  GPIOA->ODR |= (1 << 4);  // Set NSS high to deselect the device
}

uint8_t sx1278_lora_read_byte(uint8_t address)
{
  uint8_t data;
  GPIOA->ODR &= ~(1 << 4); // Set NSS low to select the device
  address &= 0x7F;         // Clear MSB for read operation
  spi_write_byte(address); // Send address
  data = spi_read_byte();  // Read data
  GPIOA->ODR |= (1 << 4);  // Set NSS high to deselect the device
  return data;
}

void sx1278_lora_send_data(uint8_t address, uint8_t *data, size_t size)
{
  /// Implementation can be added here if needed
}

void sx1278_lora_read_data(uint8_t address, uint8_t *buffer, size_t size)
{
  /// Implementation can be added here if needed
}

uint8_t sx1278_lora_set_mode(uint8_t mode)
{
  sx1278_lora_write_byte(0x01, 0x00);                                   // Set to sleep mode
  sx1278_lora_write_byte(0x01, sx1278_lora_read_byte(0x01) | (1 << 7)); // Set to sleep mode

  switch (mode)
  {
    case LORA_MODE_SLEEP:
      sx1278_lora_write_byte(0x01, sx1278_lora_read_byte(0x01) & SLEEP_MODE_MASK);
      mode_delay_ms = DELAY_FOR_SET_MODE;
      while (mode_delay_ms != 0);                ///< @todo It will be changed in future
      break;

    case LORA_MODE_STANDBY:
      sx1278_lora_write_byte(0x01, sx1278_lora_read_byte(0x01) & STANDBY_R_MASK);
      sx1278_lora_write_byte(0x01, sx1278_lora_read_byte(0x01) | STANDBY_S_MASK);
      mode_delay_ms = DELAY_FOR_SET_MODE;
      while (mode_delay_ms != 0);                ///< @todo It will be changed in future
      break;

    case LORA_MODE_TX:
      sx1278_lora_write_byte(0x01, sx1278_lora_read_byte(0x01) & TX_MODE_R_MASK);
      sx1278_lora_write_byte(0x01, sx1278_lora_read_byte(0x01) | TX_MODE_S_MASK);
      mode_delay_ms = DELAY_FOR_SET_MODE;
      while (mode_delay_ms != 0);                ///< @todo It will be changed in future
      break;

    case LORA_MODE_RX_CONTINUOUS:
      sx1278_lora_write_byte(0x01, sx1278_lora_read_byte(0x01) & CONTINUOUS_RX_R_MASK);
      sx1278_lora_write_byte(0x01, sx1278_lora_read_byte(0x01) | CONTINUOUS_RX_S_MASK);
      mode_delay_ms = DELAY_FOR_SET_MODE;
      while (mode_delay_ms != 0);                ///< @todo It will be changed in future
      break;

    case LORA_MODE_RX_SINGLE:
      sx1278_lora_write_byte(0x01, sx1278_lora_read_byte(0x01) & SINGLE_RX_R_MASK);
      sx1278_lora_write_byte(0x01, sx1278_lora_read_byte(0x01) | SINGLE_RX_S_MASK);
      mode_delay_ms = DELAY_FOR_SET_MODE;
      while (mode_delay_ms != 0);                ///< @todo It will be changed in future
      break;
    default:
      return -1;
      break;
  }
  return 0;
}

void sx1278_lora_set_channel(uint32_t frequency)
{
  uint32_t frf = (frequency * 524288) / 32000000;

  sx1278_lora_write_byte(0x06, (uint8_t)(frf >> 16));
  sx1278_lora_write_byte(0x07, (uint8_t)(frf >> 8));
  sx1278_lora_write_byte(0x08, (uint8_t)(frf));
}

void sx1278_lora_init(void)
{
  sx1278_lora_set_mode(LORA_MODE_SLEEP);
  sx1278_lora_set_channel(433);

  sx1278_lora_write_byte(0x09, 0x8f); 
  sx1278_lora_write_byte(0x0A, 0x09);
  sx1278_lora_write_byte(0x0B, 0x2B);
  sx1278_lora_write_byte(0x0C, 0x30);
  sx1278_lora_write_byte(0x1D, 0x72); 
  sx1278_lora_write_byte(0x1E, 0x70); 
  sx1278_lora_write_byte(0x1F, 0x64); 
  sx1278_lora_write_byte(0x21, 0x08); 
  sx1278_lora_write_byte(0x22, 0x01); 
  sx1278_lora_write_byte(0x23, 0xFF); 
  sx1278_lora_write_byte(0x26, 0x04); 
  sx1278_lora_write_byte(0x31, 0x03); 
  sx1278_lora_write_byte(0x37, 0x0A);
}

void sx1278_lora_tx(uint8_t byte)
{
  sx1278_lora_write_byte(0x0E, 0x00);
  sx1278_lora_write_byte(0x0D, sx1278_lora_read_byte(0x0E));
  sx1278_lora_write_byte(0x00, byte);

  sx1278_lora_set_mode(LORA_MODE_TX);
  while ((sx1278_lora_read_byte(0x12) & (1 << 3)) == 0);
  sx1278_lora_write_byte(0x12, sx1278_lora_read_byte(0x12) | (1 << 3));
}

void sx1278_lora_rx(uint8_t* byte)
{
  sx1278_lora_write_byte(0x0F, 0x00);
  sx1278_lora_set_mode(LORA_MODE_RX_CONTINUOUS);
  while((sx1278_lora_read_byte(0x12) & (1 << 6)) == 0);
  sx1278_lora_write_byte(0x12, (sx1278_lora_read_byte(0x12) & (1 << 6)));
  sx1278_lora_write_byte(0x0D, sx1278_lora_read_byte(0X10));
  *byte = sx1278_lora_read_byte(0x00);
}

void sx1278_lora_handle_TIMER_ms(void)
{
  if (mode_delay_ms != 0) {
    mode_delay_ms--;
  }
}