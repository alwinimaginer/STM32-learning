#include "cli.h"
#include "led.h"
#include "UART.h"

#include<stdint.h>
#include<string.h>

// static - only this file can access the variables
static char commandBuffer [50];
static uint8_t commandIndex = 0;
static void CLI_Execute(void);
extern RingBuffer UART_RX;

void CLI_init(void){

	commandIndex = 0;
	memset(commandBuffer, 0, sizeof(commandBuffer));

}

void CLI_process(void){
        if(!Buffer_IsEmpty(&UART_RX)){
        	char ch = Buffer_Get(&UART_RX);
        	if(ch == '\r'){
        		commandBuffer[commandIndex] = '\0';

        		CLI_Execute();

        		commandIndex = 0;
        	    memset(commandBuffer, 0, sizeof(commandBuffer));

        	}
        	else{
        		if(commandIndex < sizeof(commandBuffer) -1){
        		commandBuffer[commandIndex] = ch;
        		commandIndex ++;
        		}
        	}
        }
}

static void CLI_Execute(void){

    if(strcmp(commandBuffer, "help") == 0)
    {
        UART_SendString("\r\nAvailable Commands:\r\n");
        UART_SendString("help\r\n");
        UART_SendString("led on\r\n");
        UART_SendString("led off\r\n");
        UART_SendString("status\r\n");
    }

    else if(strcmp(commandBuffer, "led on") == 0)
        {

    	led_on();

        UART_SendString("led on\r\n");
        }
    else if(strcmp(commandBuffer, "led off") == 0)
         {

        led_off();

        UART_SendString("led off\r\n");
          }
    else if(strcmp(commandBuffer, "status") == 0)
    {
        UART_SendString("\r\nSystem Status\r\n");
        UART_SendString("----------------\r\n");

        if(LED_GetState())
        {
            UART_SendString("LED         : ON\r\n");
        }
        else
        {
            UART_SendString("LED         : OFF\r\n");
        }

        if(Buffer_IsEmpty(&UART_RX))
        {
            UART_SendString("RX Buffer   : EMPTY\r\n");
        }
        else if(Buffer_IsFull(&UART_RX))
        {
            UART_SendString("RX Buffer   : FULL\r\n");
        }
        else
        {
            UART_SendString("RX Buffer   : HAS DATA\r\n");
        }
    }
    else
    {
        UART_SendString("Unknown command\r\n");
    }
}


