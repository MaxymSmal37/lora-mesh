#include "stm32f407xx.h"
#include "system_init.h"

void clock_init(void)
{
    RCC->CR |= RCC_CR_HSEON;                                          ///< Enable HSE
    while (!(RCC->CR & RCC_CR_HSERDY));                               ///< Wait until HSE is ready

    FLASH->ACR |= FLASH_ACR_ICEN | FLASH_ACR_DCEN | FLASH_ACR_PRFTEN; ///< Enable caches and prefetch
    FLASH->ACR &= ~FLASH_ACR_LATENCY;                                 ///< Clear latency bits
    FLASH->ACR |= FLASH_ACR_LATENCY_2WS;                              ///< 2 wait states

    RCC->PLLCFGR = 0;                                                 ///< Reset PLLCFGR register
    RCC->PLLCFGR |= (8 << RCC_PLLCFGR_PLLM_Pos);                      ///< PLLM = 8 (8 MHz / 8 = 1 MHz)
    RCC->PLLCFGR |= (256 << RCC_PLLCFGR_PLLN_Pos);                    ///< PLLN = 256 (1 MHz * 256 = 256 MHz)
    RCC->PLLCFGR |= (0 << RCC_PLLCFGR_PLLP_Pos);                      ///< PLLP = 2 (gives 128 MHz)

    RCC->PLLCFGR |= (1 << RCC_PLLCFGR_PLLP_Pos);                      ///< PLLP = 4 → 64 MHz
    RCC->PLLCFGR |= RCC_PLLCFGR_PLLSRC_HSE;                           ///< Use HSE as PLL source

    
    RCC->CR |= RCC_CR_PLLON;                                          ///< Enable PLL
    while (!(RCC->CR & RCC_CR_PLLRDY));                               ///< Wait until PLL is ready

    RCC->CFGR &= ~RCC_CFGR_SW;                                        ///< Clear SW bits
    RCC->CFGR |= RCC_CFGR_SW_PLL;                                     ///< Select PLL as system clock
    while ((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_PLL);           ///< Wait until PLL is used as system clock

    RCC->CFGR &= ~(RCC_CFGR_HPRE | RCC_CFGR_PPRE1 | RCC_CFGR_PPRE2);  ///< Clear prescaler bits
    RCC->CFGR |= RCC_CFGR_HPRE_DIV1;                                  ///< AHB = 64 MHz
    RCC->CFGR |= RCC_CFGR_PPRE1_DIV2;                                 ///< APB1 = 32 MHz
    RCC->CFGR |= RCC_CFGR_PPRE2_DIV1;                                 ///< APB2 = 64 MHz

    RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;                              ///< Enable GPIOD clock
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;                              ///< Enable GPIOB clock
    RCC->APB1ENR |= RCC_APB1ENR_I2C1EN;                               ///< Enable I2C1 clock
}

void NVIC_init(void) 
{
  NVIC_SetPriority(TIM1_UP_TIM10_IRQn, 1);                            ///< Set priority
  NVIC_EnableIRQ(TIM1_UP_TIM10_IRQn);                                 ///< Enable interrupt
}

void timer_init(void)
{
  RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;                                 ///< Enable TIM1 clock

  TIM1->PSC = 64 - 1;                                                 ///< Prescaler: 64 MHz / 64 = 1 MHz
  TIM1->ARR = 1000 - 1;                                               ///< Auto-reload: 1000 ticks -> 1 millisecond
  TIM1->DIER |= TIM_DIER_UIE;                                         ///< Enable update interrupt
  TIM1->CR1 |= TIM_CR1_CEN;                                           ///< Enable timer
}

void gpio_init(void)
{
  // Mode
  GPIOB->MODER &= ~((3<<16) | (3<<18));                               ///< Clear mode bits for PB8 and PB9
  GPIOB->MODER |=  ((2<<16) | (2<<18));                               ///< Set alternate function mode for PB8 and PB9
  GPIOD->MODER &= ~((3<<24) | (3<<26));                               ///< Clear mode bits for PD12 and PD13
  GPIOD->MODER |= ((1<<24) | (1<<26));                                ///< Set output mode for PD12 and PD13

  GPIOB->OTYPER &= ~((1<<8) | (1<<9));                                ///< Clear output type bits for PB8 and PB9
  GPIOB->OTYPER |=  ((1<<8) | (1<<9));                                ///< Set output type to open-drain for PB8 and PB9

  GPIOB->OSPEEDR &= ~((3<<16) | (3<<18));                             ///< Clear speed bits for PB8 and PB9
  GPIOB->OSPEEDR |=  ((3<<16) | (3<<18));                             ///< Set high speed for PB8 and PB9

  GPIOB->PUPDR &= ~((3<<16) | (3<<18));                               ///< Clear pull-up/pull-down bits for PB8 and PB9
  GPIOB->PUPDR |=  ((1<<16) | (1<<18));                               ///< Set pull-up for PB8 and PB9

  GPIOB->AFR[1] |= ((4<<0) | (4<<4));                                 ///< Set AF4 (I2C1) for PB8 and PB9
}

void uart_init(void)
{
  // Placeholder for UART initialization
}

void i2c_init(void)
{
  I2C1->CR1 |= I2C_CR1_SWRST;                                        ///< Enter reset state
  I2C1->CR1 &= ~I2C_CR1_SWRST;                                       ///< Exit from reset state

  I2C1->CR2 &= ~I2C_CR2_FREQ;                                        ///< Clear frequency bits
  I2C1->CR2 |= 16;                                                   ///< APB1 clock frequency in MHz
  I2C1->CCR &= ~I2C_CCR_CCR;                                         ///< Clear CCR bits
  I2C1->CCR |= 80;                                                   ///< 100 kHz standard mode (16MHz / (2 * 100kHz))

  I2C1->TRISE &= ~0x3F;                                              ///< Clear TRISE bits
  I2C1->TRISE |= 17;                                                 ///< Maximum rise time for 100 kHz (1000ns / 62.5ns)

  I2C1->CR1 |= I2C_CR1_PE;                                           ///< Enable the peripheral
}

void spi_init(void)
{
  // Placeholder for SPI initialization
}

void sys_init(void)
{
    clock_init();
    NVIC_init();
    timer_init();
    gpio_init();
    uart_init();
    i2c_init();
    spi_init();
}
