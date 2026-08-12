#include "UART.h"
#include "led.h"
#include "cli.h"

char Userpassword[20];
extern RingBuffer UART_RX;                              // its a structure

int main(void)
{
    UART_Init();
    LED_Init();
    Buffer_init(&UART_RX);   // in the address UART_RX init bufferin UART.C
    CLI_init();

    UART_SendString("\r\nSTM32 CLI\r\n");
    UART_SendString("Type 'help' for available commands.\r\n");
    UART_SendString("STM32 > ");

    while(1)
    {

    CLI_process();

    }
  }

