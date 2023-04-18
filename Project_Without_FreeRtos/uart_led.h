#ifndef UART_H
#define UART_H

/*HEADER FILE FOR UART */

#include "stm32f10x.h"  

void Uart2Config (void);
void UART2_SendString (char *string);
uint8_t UART2_GetChar (void);
void UART2_SendChar (uint8_t c);





	

#endif /* UART HEADER FILE */
