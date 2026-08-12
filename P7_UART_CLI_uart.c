//                                 UART INTERRUPT DRIVER

#include "UART.h"

RingBuffer UART_RX; // the memory is actually created here only for the structure.

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

	//Enable USART interrupt
	USART2->CR1 |= USART_RXNEIE;

	// Enable USART2 interrupt in NVIC
	NVIC_ISER1 |= ISER1_ENABLE;

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
		UART_SendChar(*str);             // go to main code to see its implementation
		str ++;                          // pointer arithmatic
	}

}

// no read function is required
// only interrupt function is required

void USART2_IRQHandler(void){

	if (USART2->SR & USART_RXNE){

	     char ch = USART2->DR; //only receiver operation is performed here
	     Buffer_Put(&UART_RX, ch);
	}
}

void Buffer_init(RingBuffer *rb){
	    rb->head = 0;
		rb->tail = 0;
}

uint8_t Buffer_IsEmpty(RingBuffer *rb){

	return (rb->head == rb->tail);
}

uint8_t Buffer_IsFull(RingBuffer *rb){
	 return((rb->head+1) % BUFFER_SIZE == rb->tail);

}


void Buffer_Put(RingBuffer *rb, char data)
{
	if(Buffer_IsFull(rb)){

		UART_SendString("Dropped: ");
		UART_SendChar(data);
		UART_SendString("\r\n");

		return;
	}

    rb->rxbuffer[rb->head] = data;

    rb->head = (rb->head + 1) % BUFFER_SIZE;
}

char Buffer_Get(RingBuffer *rb)
{
    char data;

    data = rb->rxbuffer[rb->tail];

    rb->tail = (rb->tail + 1) % BUFFER_SIZE;

    return data;
}

void Delay(uint32_t DelayCount){

	volatile uint32_t i;
	for(i = 0; i < DelayCount; i++);

}




