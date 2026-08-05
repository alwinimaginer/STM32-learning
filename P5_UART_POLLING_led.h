#ifndef LED_H
#define LED_H
#include <stdint.h>
// PROTOTYPES, FUNCTION POINTERS AND DEFINITIONS -> .h FILE

typedef void(*LED_Function)(void); // declaring function pointer


#define IOPAEN       (1 << 2)
#define LED_PIN0     (1 << 5)               // PA5
#define LED_PIN1     (1 << 6)               // PA6
#define LED_PIN2     (1 << 7)               // PA7

void LED_Init(void);

void delay(uint32_t delayCount);

void red_led(void);
void yellow_led(void);
void green_led(void);

#endif
