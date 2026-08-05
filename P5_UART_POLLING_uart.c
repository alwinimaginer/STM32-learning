//                              UART DRIVER

#include "UART.h"

void UART_Init(void){

	// enable RCC for GPIOA pins ( 1 << 2 )
	RCC_APB2ENR |= IOPAEN;

	// enable clock for USART2 peripheral ( 1 << 17 )
	RCC_APB1ENR |= USART2EN;

    // configure PA2 and tell that USART is the primary function
	// TRANSMITTER PIN - TX
	// 10   10  |CNF  10: Alternate function output Push-pull
    // CNF MODE |MODE 10: Output mode, max speed 2 MHz.
	GPIOA->CRL &= ~(0xF << 8);
	GPIOA->CRL |=  (0xA << 8);

	// configure PA3
	// RECIEVER PIN   - RX
	// 01   00   | CNF  01: Floating input (reset state)
	// CNF MODE  | MODE 00: Input mode (reset state)
	GPIOA->CRL &= ~(0XF << 12);
	GPIOA->CRL |=  (0x4 << 12);

	// configure baud rate
	USART2->BRR = 0x45;

	// enable TE ( 1 << 3 )   /* make sure you use |= and not = for this */
	USART2->CR1 |= USART_TE;

	// enable RE ( 1 << 2 )
	USART2->CR1 |= USART_RE;

	// enable UE ( 1 << 13 )
	USART2->CR1 |= USART_UE;

}

void UART_SendChar(char ch){
	while (!(USART2->SR & USART_TXE)){
		// wait till TXE == 1
	}
	USART2->DR = ch; // DR stores the data
}

void UART_SendString (const char *str){  //const is used so that
	                                   //so that the data is not overwrited.
	while(*str != '\0'){
		UART_SendChar(*str);
		str ++;
	}

}

char UART_ReadChar(void){

	while(!(USART2->SR & USART_RXNE)){
		// Wait till RXNE == 1
	}
	 char ch = USART2->DR;

	 return ch;
}

void UART_ReadString(char *buffer, uint32_t maxLength){

	 uint32_t i = 0;
	 while(i < (maxLength-1)){
		 char ch = UART_ReadChar();
		 if(ch == '\r'){
		    break;
		 }
		 buffer[i] = ch;
		 i ++;
	 }
	    buffer[i] = '\0';
}

