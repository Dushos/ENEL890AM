


#include "stm32f10x.h"                  // Device header

void Uart2Config (void);

void UART2_SendChar (uint8_t c);

void UART2_SendString (char *string);

extern volatile uint8_t receivedData;

void USART2_IRQHandler(void);

