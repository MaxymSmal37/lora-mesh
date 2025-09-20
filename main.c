#include "stm32f407xx.h"
#include "system_init.h"
#include "display.h"
#include "Config.h"

typedef struct {
  uint32_t counter100ms;
  uint32_t counter500ms;
  uint32_t counter1000ms;
} sysTimers;

volatile sysTimers timers;

int main(void)
{
  timers.counter100ms = TIMER_100_MS;
  timers.counter500ms = TIMER_500_MS;
  timers.counter1000ms = TIMER_1000_MS;

  sys_init();
  ssd1306_InitDisplay();
  GPIOD->ODR |= (1 << 12);

  while (1)
  {
    GPIOD->ODR ^= (1 << 12);
    for (volatile int i = 0; i < 10000000; i++)
      ;
    ssd1306_DemoAnimation();
  }
}
void TIM1_UP_TIM10_IRQHandler(void)
{
  if (TIM1->SR & TIM_SR_UIF) 
  {
    TIM1->SR &= ~TIM_SR_UIF; // Clear interrupt flag

    if (timers.counter1000ms > 0)
    {
      timers.counter1000ms--;
    }

    if (timers.counter1000ms == 0)
    {
      timers.counter1000ms = TIMER_1000_MS; // reload 1000ms
      GPIOD->ODR ^= (1 << 13);              
    }
  }
}