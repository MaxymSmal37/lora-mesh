#include "stm32f407xx.h"

#include "stdint.h"
#include "stdio.h"

#include "Error_Loc.h"
#include "Error_Pub.h"
#include "display.h"
#include "Logger.h"

uint8_t error_hanle_flag = 0;

void set_error(uint8_t error_code)
{
  if (error_code < 50) 
  {
    while (1)
    {
      if (error_hanle_flag == 1)
      {
        switch (error_code)
        {
          case APP_SPI_ERROR:
            CRITICAL_LOG("Failed SPI connect . . . .\n\r");
            break;
        
          case APP_UNDEFINED_SX1278_MODULE:
            CRITICAL_LOG("Failed to define sx1278 lora module . . . .\n\r");
            print_error(error_code);
            break;

          default:
            break;
        }
        togle_error_led();
        error_hanle_flag = 0;
      }
    }
  }
  else
  {
    switch (error_code)
    {
      case APP_LORA_READ_ERROR:
        ERROR_LOG("Failed to read data from lora . . . .\n\r");
        break;
        
      case APP_LORA_WRITE_ERROR:
        ERROR_LOG("Failed to write data to lora . . . .\n\r");
        break;

      default:
        break;
    }

  }
}

void togle_error_led(void)
{
  GPIOD->ODR ^= (1 << 14);  
}

void print_error(uint8_t error) 
{
  switch (error)
  {
  case APP_UNDEFINED_SX1278_MODULE:
    ssd1306_ClearDisplay();
    ssd1306_SetCursor(15, 0);
    ssd1306_PutString("Undefined Lora module");
    break;
  
  default:
    break;
  }
}

void handle_sys_error(void)
{
  error_hanle_flag = 1;
}

void error_routine(uint8_t error_code)
{
 
}
