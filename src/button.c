#include "button.h"
#include "stm32f0xx.h"

// le bouton est sur le pin 13 du GPIO C

void button_init() {
    // on allume l'horloge du GPIOC
    SET_BIT(RCC->AHBENR, RCC_AHBENR_GPIOCEN);

    // on met la broche 13 du GPIOC en entrée
    CLEAR_BIT(GPIOC->MODER, GPIO_MODER_MODER13_Msk);
}

int button_pressed() {
    // la broche est à 0 lorsque l'on appuie
    // et 1 lorsque l'on n'appuie pas
    // on renvoie l'inverse
    return !READ_BIT(GPIOC->IDR, GPIO_IDR_13);
}
