#include "led.h"                             // header file which contains the protopyes of functions
#include <stdint.h>                          // used for accessing uint32_t datatype for 32 bit register mcu.

typedef enum {                                // Enum for different states of light
	RED,                                      // RED = 0 , if not declared any value and GREEN is one and so on.
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
