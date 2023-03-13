
#include "stm32f10x.h"
#include "uart_led.h"

void GPIO_Config (void)
{
/************** STEPS TO FOLLOW *****************
	1. Enable the GPIOA clock
	2. Configure the Pin as output
************************************************/
	
	RCC->APB2ENR |= (1<<2);  // Enable GPIOA Clock
	
	GPIOA->CRL |= ((1<<20) | (1<<21));  // PC5 Output mode 10 MHz, push pull
	GPIOA->CRL &= ~( (1<<22) | (1<<23));
}
