#ifndef LED_H
#define LED_H
#include <stdint.h>
// PROTOTYPES, FUNCTION POINTERS AND DEFINITIONS -> .h FILE

typedef void(*LED_Function)(void); // declaring function pointer


#define IOPAEN       (1 << 2)
#define LED_PIN0     (1 << 5)               // PA5


void LED_Init(void);

void delay(uint32_t delayCount);

void led_on(void);

void led_off(void);

uint8_t LED_GetState(void);

#endif
