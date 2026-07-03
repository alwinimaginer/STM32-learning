#include "led.h"
#include <stdint.h>

typedef enum {                                // Enum for different states of light
	RED,
	YELLOW,
	GREEN
}trafficstate;

typedef struct {                              // defining structure
	LED_Function action;                      // function pointer
	trafficstate nextstate;                   // Enum
	uint32_t delaycount;                      // delay variable
}statemachine;

statemachine traffictable[] = {               //defining values to structure
	{ red_led,    YELLOW, 1000000 },
    { yellow_led, GREEN,  2000000 },
    { green_led,  RED,    3000000 }
};

int main(void){

	LED_Init();                                // initializing GPIO, clock and defining fxn and constants

	trafficstate state = RED;                  // initializing the state

	while(1){                                  // assigning the values to structure

		traffictable[state].action();          // to execute the current light function

		delay(traffictable[state].delaycount); // to execute current light delay

		state = traffictable[state].nextstate; // to change the state
		}

}
