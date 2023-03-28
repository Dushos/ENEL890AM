
#include "stm32f10x.h"
#include "Delay_F103.h"
#include "uart_main.h"


void Uart2Config(void) {

    RCC->APB1ENR |= (1 << 17);  // ENABLE USART 2 CLOCK
    RCC->APB2ENR |= (1 << 2);   // ENABLE GPIOA

    GPIOA->CRL = 0;
    GPIOA->CRL |= (3 << 8);    // OUTPUT MODE 50 MHz for PA2
    GPIOA->CRL |= (2 << 10);   // ALTERNATE FUNC PUSH PULL for PA2

    GPIOA->CRL &= ~(3 << 12);  // INPUT MODE for PA3
    GPIOA->CRL |= (2 << 14);   // INPUT PULL UP/ DOWN for PA3

    // ENABLE THE USART BY WRITING THE UE BIT IN USART_CR1 REGISTER TO 1.
    USART2->CR1 = 0x00;          // CLEAR ALL
    USART2->CR1 |= (1 << 13);    // UE = 1... ENABLE USART

    // PROGRAM THE M BIT IN USART_CR1 TO DEFINE THE WORD LENGTH.
    USART2->CR1 &= ~(1 << 12);   // M =0; 8 BIT WORD LENGTH

    // RR REGISTER.
    USART2->BRR = (9 << 0) | (19 << 4);   // BAUD RATE OF 115200, PCLK1 AT 45MHZ

    // ENABLE THE TRANSMITTER/RECEIVER BY SETTING THE TE AND RE BITS IN USART_CR1 REGISTER
    USART2->CR1 |= (1 << 2);  // RE=1.. ENABLE THE RECEIVER
    USART2->CR1 |= (1 << 3);  // TE=1.. ENABLE TRANSMITTER

    // ENABLE INTERRUPT ON RXNE FLAG
    USART2->CR1 |= (1 << 5);  // RXNEIE = 1

    // ENABLE USART2 NVIC INTERRUPT
    NVIC_EnableIRQ(USART2_IRQn);
}

void UART2_SendChar(uint8_t c) {
    //Send char to the screen
    USART2->DR = c;                 // LOAD THE DATA INTO DR REGISTER
    while (!(USART2->SR & (1 << 6)));  // WAIT FOR TC TO SET.. THIS INDICATES THAT THE DATA HAS BEEN TRANSMITTED
}

void UART2_SendString(char *string) {
    while (*string) UART2_SendChar(*string++);
}

volatile uint8_t receivedData = 0;

void USART2_IRQHandler(void) {
    if (USART2->SR & USART_SR_RXNE)  // CHECK IF DATA IS RECEIVED
    {
        receivedData = USART2->DR;  // READ THE RECEIVED DATA
    }
}

