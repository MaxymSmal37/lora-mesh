#include "stm32f407xx.h"

void delay(volatile uint32_t count) {
    while(count--) { __NOP(); }
}

int main(void) {
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;
    GPIOD->MODER |= (1<<24);  // PD12 output

    while(1) {
        GPIOD->ODR ^= (1<<12);
        for(volatile int i=0;i<1000000;i++);
    }
}