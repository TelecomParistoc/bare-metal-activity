#include <stdint.h>

#include "handlers.h"
#include "irq.h"

#define VTOR (*(volatile uint32_t *)0xE000ED08)
#define NVIC_ISER (*(volatile uint32_t *)0xE000E100)
#define NVIC_ICER (*(volatile uint32_t *)0xE000E180)
#define NVIC_ISPR (*(volatile uint32_t *)0xE000E200)
#define NVIC_ICPR (*(volatile uint32_t *)0xE000E280)

/* IRQ vectors table */
extern uint32_t *_stack;
extern void _start(void);

void *vector_table[] __attribute__((section(".vectors"))) = {
    // Stack and Reset Handler
    &_stack, /* Top of stack */
    _start,  /* Reset handler */

    // ARM internal exceptions
    NMI_Handler,       /* NMI handler */
    HardFault_Handler, /* Hard Fault handler */
    SVC_Handler,       /* SVC handler */
    PendSV_Handler,    /* Pending SVC handler */
    SysTick_Handler,   /* SysTick hanlder */
    WWDG_Handler, 0, RTC_Handler, FLASH_Handler, RCC_Handler, EXTI0_1_Handler,
    EXTI2_3_Handler, EXTI4_15_Handler, 0, DMA_CH1_Handler, DMA_CH2_3_Handler,
    DMA_CH4_5_Handler, ADC_Handler, TIM1_BRK_UP_TRG_COM_Handler,
    TIM1_CC_Handler, 0, TIM3_Handler, TIM6_Handler, 0, 0, TIM14_Handler,
    TIM15_Handler, TIM16_Handler, TIM17_Handler, I2C1_Handler, I2C2_Handler,
    SPI1_Handler, SPI2_Handler, USART1_Handler, USART2_Handler,
    USART3_4_5_6_Handler, 0, USB_Handler};

extern char _irq_table;

void irq_init() {
    // Relocate VTOR table
    VTOR = (uint32_t)&_irq_table;
}

void irq_enable(int irq_number) { NVIC_ISER |= (1 << irq_number); }

void irq_disable(int irq_number) { NVIC_ICER |= (1 << irq_number); }
