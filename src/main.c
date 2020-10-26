#include "../lib/irq.h"
#include "stm32f0xx.h"

int main() {
    irq_init();

    SET_BIT(RCC->AHBENR, RCC_AHBENR_GPIOAEN | RCC_AHBENR_GPIOCEN);

    GPIOA->MODER =
        (GPIOA->MODER & ~GPIO_MODER_MODER5_Msk) | GPIO_MODER_MODER5_0;

    CLEAR_BIT(GPIOC->MODER, GPIO_MODER_MODER13_Msk);

    while (1) {
        if (READ_BIT(GPIOC->IDR, GPIO_IDR_13)) {
            SET_BIT(GPIOA->BSRR, GPIO_BSRR_BR_5);
        } else {
            SET_BIT(GPIOA->BSRR, GPIO_BSRR_BS_5);
        }
    }
}
