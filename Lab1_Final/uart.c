

#include "stm32f10x.h"
#include "uart_led.h"

void Uart2Config (void){

	RCC->APB1ENR |= (1<<17); //ENABLE USART 2 CLOCK
	RCC->APB2ENR |= (1<<2); // ENABLE GPIOA
	
		
		GPIOA->CRL = 0;
		GPIOA->CRL |= (3<<8);   // output mode 50 MHz for PA2
		GPIOA->CRL |= (2<<10);  // Alternate Func Push Pull For PA2
	
		GPIOA->CRL &= ~(3<<12);   // Intput Mode For PA3
		GPIOA->CRL |= (2<<14);  // Input Pull Up/ Down For PA3	

	
	// 3. Enable the USART by writing the UE bit in USART_CR1 register to 1.
	USART2->CR1 = 0x00;  // clear all
	USART2->CR1 |= (1<<13);  // UE = 1... Enable USART
	
	// 4. Program the M bit in USART_CR1 to define the word length.
	USART2->CR1 &= ~(1<<12);  // M =0; 8 bit word length
	
	// RR register.
	USART2->BRR = (9<<0) | (19<<4);   // Baud rate of 115200, PCLK1 at 45MHz
	
	// 6. Enable the Transmitter/Receiver by Setting the TE and RE bits in USART_CR1 Register
	USART2->CR1 |= (1<<2); // RE=1.. Enable the Receiver
	USART2->CR1 |= (1<<3);  // TE=1.. Enable Transmitter


}


void UART2_SendChar (uint8_t c)
{
		/*********** STEPS FOLLOWED *************
	
	1. Write the data to send in the USART_DR register (this clears the TXE bit). Repeat this
		 for each data to be transmitted in case of single buffer.
	2. After writing the last data into the USART_DR register, wait until TC=1. This indicates
		 that the transmission of the last frame is complete. This is required for instance when
		 the USART is disabled or enters the Halt mode to avoid corrupting the last transmission.
	
	****************************************/
	
	USART2->DR = c; // load the data into DR register
	while (!(USART2->SR & (1<<6)));  // Wait for TC to SET.. This indicates that the data has been transmitted
}

void UART2_SendString (char *string)
{
	while (*string) UART2_SendChar (*string++);
}


uint8_t UART2_GetChar (void)
{
			/*********** STEPS FOLLOWED *************
	
	1. Wait for the RXNE bit to set. It indicates that the data has been received and can be read.
	2. Read the data from USART_DR  Register. This also clears the RXNE bit
	
	****************************************/

	uint8_t temp;
	
	while (!(USART2->SR & (1<<5)));  // wait for RXNE bit to set
	temp = USART2->DR;  // Read the data. This clears the RXNE also
	return temp;
}
	

