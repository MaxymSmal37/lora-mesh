#include "stm32f407xx.h"

extern unsigned int _sidata, _sdata, _edata;
extern unsigned int _sbss, _ebss;

void init_data_bss(void) {
    unsigned int *src = &_sidata;
    unsigned int *dst = &_sdata;
    while (dst < &_edata) *dst++ = *src++;
    dst = &_sbss;
    while (dst < &_ebss) *dst++ = 0;
}

void SystemInit(void) {
#if (__FPU_PRESENT == 1) && (__FPU_USED == 1)
    SCB->CPACR |= ((3UL << 20) | (3UL << 22));
#endif
    RCC->CR |= 0x00000001U;
}

