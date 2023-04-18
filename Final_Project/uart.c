

#include "stm32f10x.h"
#include "uart_led.h"
#include "minimal_regs.h"
#include <stdio.h>

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
	
	/*USART2->CR1 |= (1 << 5);  // RXNE interrupt enable
	
	// Enable USART2 interrupt in NVIC
    NVIC->ISER[0] |= (1 << 6);
		NVIC_SetPriority(USART2_IRQn, 1); // Set USART2 interrupt priority to 1 (higher than default priority)
		//NVIC_EnableIRQ(USART2_IRQn); // Enable USART2 interrupt
    */


}


void UART2_SendChar (uint8_t c)
{
			
	USART2->DR = c; // load the data into DR register
	while (!(USART2->SR & (1<<6)));  // Wait for TC to SET.. This indicates that the data has been transmitted
}

void UART2_SendString (char *string)
{
	while (*string) {
        if (*string == '\n') {
            UART2_SendChar('\r');  // send the carriage return character
        }
        UART2_SendChar (*string++);
		}
}




uint8_t UART2_GetChar (void)
{
			
	uint8_t temp;
	
	while (!(USART2->SR & (1<<5)));  // wait for RXNE bit to set
	temp = USART2->DR;  // Read the data. This clears the RXNE also
	return temp;
}





/*void USART2_IRQHandler(void)
{
    // Check if the interrupt was triggered by a received character
    if ((USART2->SR & USART_SR_RXNE) != 0)
    {
        // Read the received character from the USART's data register
        uint8_t received_char = USART2->DR;

        // Do something with the received character...
        // For example, echo it back to the sender
        USART2->DR = received_char;

        // Clear the interrupt by setting the RXNE bit in the USART's status register
        USART2->SR &= ~USART_SR_RXNE;
    }
}

*/
