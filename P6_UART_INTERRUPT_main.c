#include "UART.h"

char Userpassword[20];
extern RingBuffer UART_RX;                              // its a structure

int main(void)
{
    UART_Init();
    Buffer_init(&UART_RX);                              // in the address UART_RX init bufferin UART.C

    UART_SendString("UART Interrupt Echo Project\r\n");
    UART_SendString("Type any character...\r\n");

    while(1)
    {
    	if (!Buffer_IsEmpty(&UART_RX))                 // if buffer is not empty,get the tail data
    	{

    	        char ch = Buffer_Get(&UART_RX);        // go to add of UART_RX and get the get it.
                Delay(1000000);                        // artificial delay to create other tasks
                                                       // that might be running in main other than this

    	    	UART_SendString("\r\n");
    	        UART_SendChar(ch);
    	        UART_SendString("\r\n");
    	    }
    	}
    }

