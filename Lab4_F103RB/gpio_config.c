
#include <stm32f10x.h>
#include "adc.h"

void ADC_GPIO_Init(void) {
   
	 	// Enable clock for GPIOA
    RCC->APB2ENR |= (1<<2);
		
		

    // Set PA1 as analog input
    GPIOA->CRL = 0;    // Clear bits 4-7
    GPIOA->CRL |= (0x0<<4);     // Set bits 4-7 to 0b0000 (analog mode)

}

