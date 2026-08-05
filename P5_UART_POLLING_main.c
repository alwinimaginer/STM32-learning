#include "password.h"
#include "UART.h"
#include "led.h"

char Userpassword[20];

int main(void)
{
    UART_Init();
    LED_Init();

    while(1)
    {
    	UART_SendString("\r\n");
    	UART_SendString("========================\r\n");
    	UART_SendString(" STM32 SECURITY SYSTEM\r\n");
    	UART_SendString("========================\r\n");

    	UART_SendString("Enter Password: ");

    	UART_ReadString(Userpassword,20);

    	if(Password_Check(Userpassword)){     // CORRECT_PASSWORD = 1
    		green_led();
    		UART_SendString("\r\nACCESS GRANTED\r\n");
    	}

    	else{                                 // PASSWORD_ERROR = 0
    		red_led();
    		UART_SendString("\r\nACCESS DENIED\r\n");
    	}
    }
}

