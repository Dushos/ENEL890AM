#ifndef UART_H
#define UART_H

/*HEADER FILE FOR UART */

#include "stm32f10x.h"  

void Uart2Config (void);
void UART2_SendString (char *string);
uint8_t UART2_GetChar (void);
void UART2_SendChar (uint8_t c);
void USART2_IRQHandler(void);



// LAB 3 HEADER FILES
	void handleRawInput(int value);
	void handlePercentageInput(int value);
	
	
	

#endif /* UART HEADER FILE */
