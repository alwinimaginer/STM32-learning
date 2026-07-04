#ifndef LED_H
#define LED_H
#include <stdint.h>
// PROTOTYPES, FUNCTION POINTERS AND DEFINITIONS -> .h FILE

// 1) enable clock
#define RCC_APB2ENR (*(volatile uint32_t *)0x40021018)

typedef struct  //2)STRUCTURES // I can use it for GPIOA, GPIOB, GPIOC
{
    volatile uint32_t CRL;
    volatile uint32_t CRH;
    volatile uint32_t IDR;
    volatile uint32_t ODR;
} GPIO_TypeDef;

typedef void(*LED_Function)(void); // declaring function pointer

#define GPIOA ((GPIO_TypeDef *)0x40010800) // GPIOA->ODR possible

#define IOPAEN (1 << 2)
#define LED_PIN0     (1 << 5)
#define LED_PIN1     (1 << 6)
#define LED_PIN2     (1 << 7)

void LED_Init(void);
void delay(uint32_t delayCount);

void red_led(void);
void yellow_led(void);
void green_led(void);

#endif
