#ifndef UART_H
#define UART_H
#include <stdint.h>

#define RCC_APB2ENR (*(volatile uint32_t*) 0x40021018)
#define RCC_APB1ENR (*(volatile uint32_t*) 0x4002101C)

#define IOPAEN     (1 << 2)   //  GPIOA clock enable
#define USART2EN   (1 << 17)  //  USART clock enable
#define USART_TE   (1 << 3)   //  enable transmitter pin
#define USART_RE   (1 << 2)   //  enable receiver pin
#define USART_UE   (1 << 13)  //  enable USART
#define USART_TXE  (1 << 7)   //  to check the status of TXE
#define USART_RXNE (1 << 5)   //  to check the status of RXNE

typedef struct  //2)STRUCTURES, I can use it for GPIOA, GPIOB, GPIOC
{
    volatile uint32_t CRL;
    volatile uint32_t CRH;
    volatile uint32_t IDR;
    volatile uint32_t ODR;
} GPIO_TypeDef;

#define GPIOA ((GPIO_TypeDef*)0x40010800) // GPIOA->ODR possible

typedef struct
{
	volatile uint32_t SR;
	volatile uint32_t DR;
	volatile uint32_t BRR;
	volatile uint32_t CR1;
}USART_TypeDef;

#define USART2 ((USART_TypeDef*)0x40004400)

/* Function Prototypes */

void UART_Init(void);

void UART_SendChar(char ch);

void UART_SendString(const char *str);
// const is used so that the function can only read the argument and not to overwrite it.

char UART_ReadChar(void);

void UART_ReadString(char *buffer, uint32_t maxLength);
// buffer is used for storing the output here !!

#endif

