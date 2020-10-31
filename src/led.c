#include "led.h"
#include "stm32f0xx.h"

// la led est sur le pin 4 du GPIO A

void led_init() {
    // on allume l'horloge du GPIOA
    SET_BIT(RCC->AHBENR, RCC_AHBENR_GPIOAEN);

    // on met la broche 5 du GPIOA en sortie
    GPIOA->MODER =
        (GPIOA->MODER & ~GPIO_MODER_MODER5_Msk) | GPIO_MODER_MODER5_0;
}

void led_on() {
    // on met la broche à 1
    SET_BIT(GPIOA->BSRR, GPIO_BSRR_BS_5);
}

void led_off() {
    // on met la broche à 0
    SET_BIT(GPIOA->BSRR, GPIO_BSRR_BR_5);
}
