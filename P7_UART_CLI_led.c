#include "led.h"
#include "UART.h"

static uint8_t ledState = 0;

void LED_Init(void){
	    // enble clock for bus 2
	     RCC_APB2ENR |= IOPAEN;

		// PA5 OUTPUT - bits 23,22,21,20
		// 20,21 - mode , 22,23 - CNF
		 GPIOA->CRL &= ~(0xF << 20);
	    // 20,21 - 10: Output mode, max speed 2 MHz.
	    // In output mode (MODE[1:0] > 00):
		// 22,23 - 00: General purpose output push-pull
		 GPIOA->CRL |=  (0x2 << 20);

}

void delay(uint32_t delayCount){
	volatile uint32_t i;
	for(i = 0; i < delayCount ; i ++);
}

void led_on(){
	ledState = 1;
	GPIOA->ODR |= LED_PIN0; // turn ON red LED
}

void led_off(){
	ledState = 0;
	GPIOA->ODR &= ~LED_PIN0;
}

uint8_t LED_GetState(void)
{
    return ledState;
}
