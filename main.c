#include <stdio.h>

#include "stm32f407xx.h"

#include "system_init.h"
#include "display.h"
#include "uart.h"
#include "sx1278_lora.h"
#include "Error_Loc.h"
#include "Error_Pub.h"
#include "Config.h"

typedef struct {
  uint32_t counter100ms;
  uint32_t counter500ms;
  uint32_t counter1000ms;
} sysTimers;

volatile sysTimers timers;
volatile char uart_rx_data;

uint8_t error_blink_flag = 0;

uint8_t rxData = 0;

int main(void)
{
  timers.counter100ms = TIMER_100_MS;
  timers.counter500ms = TIMER_500_MS;
  timers.counter1000ms = TIMER_1000_MS;

  sys_init();
  GPIOA->ODR |= (1 << 4);   
  ssd1306_InitDisplay();
  sx1278_lora_init();

  if (sx1278_lora_get_regVersion() != 0x12)
  {
    set_error(APP_UNDEFINED_SX1278_MODULE);
  }

  GPIOD->ODR |= (1 << 12);

  while (1)
  {
    for (volatile int i = 0; i < 10000000; i++);
    ssd1306_DemoAnimation();
    printf("Demo Animation Completed\n");
    sx1278_lora_rx(&rxData);

    if(rxData == 0x55)
    {
      GPIOD->ODR ^= (1 << 12);
    }
  }
}

int __io_putchar(int ch)  
{
  uart_send_char((char)ch);
  return ch;
}

void TIM1_UP_TIM10_IRQHandler(void)
{
  if (TIM1->SR & TIM_SR_UIF) 
  {
    TIM1->SR &= ~TIM_SR_UIF; // Clear interrupt flag

    sx1278_lora_handle_TIMER_ms();

    if (--timers.counter500ms == 0)
    {
      timers.counter500ms = TIMER_500_MS; // reload 500ms           
      handle_sys_error();
    }

    if (--timers.counter1000ms == 0)
    {
      timers.counter1000ms = TIMER_1000_MS; // reload 1000ms
      GPIOD->ODR ^= (1 << 13);              
    }
  }
}

void USART1_IRQHandler(void)
{
    if (USART1->SR & USART_SR_RXNE)  // Check if RX not empty
    {
        uart_rx_data = (char)USART1->DR; // Read received byte
        uart_send_char(uart_rx_data);        // Echo back
    }
}