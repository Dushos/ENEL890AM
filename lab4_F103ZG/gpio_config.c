
#include <stm32f10x.h>
#include "adc.h"

void ADC_GPIO_Init(void) {
   
	 // enable GPIOC 
		RCC->APB2ENR = (1 << 4) ;
	
	//Set PC0 to input mode
	GPIOC->CRL = 0;
	GPIOC->CRL = 0x0 << 0 ;

}

