#include "button.h"
#include "led.h"
#include "stm32f0xx.h"

int main() {
    // initialisation de la led et du bouton
    led_init();
    button_init();

    while (1) {
        if (button_pressed()) {
            led_on();
        } else {
            led_off();
        }
    }
}
