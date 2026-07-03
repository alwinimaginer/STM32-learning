#include "led.h"

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

		// PA6 OUTPUT - bits 24,25,26,27
	    // 24,25 - mode , 26,27 - CNF
		 GPIOA->CRL &= ~(0xF << 24);
		// 24,25 - 10: Output mode, max speed 2 MHz.
		// In output mode (MODE[1:0] > 00):
		// 26,27 - 00: General purpose output push-pull
		 GPIOA->CRL |=  (0x2 << 24);

		// PA7 OUTPUT - bits 28,29,30,31
		// 28,29 - mode , 30,31 - CNF
		 GPIOA->CRL &= ~(0xF << 28);
		// 28,29 - 10: Output mode, max speed 2 MHz.
		// In output mode (MODE[1:0] > 00):
		// 30,31 - 00: General purpose output push-pull
		 GPIOA->CRL |=  (0x2 << 28);

}

void delay(uint32_t delayCount){
	volatile uint32_t i;
	for(i = 0; i < delayCount ; i ++);
}

void red_led(){
	GPIOA->ODR &= ~(LED_PIN1|LED_PIN2);
	GPIOA->ODR |= LED_PIN0;
}

void yellow_led(){
	GPIOA->ODR &= ~(LED_PIN0|LED_PIN2);
	GPIOA->ODR |= LED_PIN1;
}

void green_led(){
	GPIOA->ODR &= ~(LED_PIN0|LED_PIN1);
	GPIOA->ODR |= LED_PIN2;
}
