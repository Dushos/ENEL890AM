
#include <stm32f10x.h>
#include "adc.h"



void ADC_Config(void){

	// Enable clock for ADC1
	RCC->APB2ENR |= (1 << 9) ;
	
	// Set channel 10 to be scanned first
	ADC1->SQR3 = 0;
	ADC1->SQR3 = (0xA << 0) ;

	
	// Set sample time for channel 10 to 55.5 cycles
	ADC1->SMPR1 |= 0x5 << 0;

	
	// Enable scan mode
	ADC1->CR1 |= (1 << 8);

	// Enable interrupt for end-of-conversion
	ADC1->CR1 |= (1 << 5);

	// Enable external triggering
	ADC1->CR2 |= (1 << 20);

	// Select SWSTART as the external event
	ADC1->CR2 |= (0x7 << 17);

	// Turn on the ADC
	ADC1->CR2 |= (1 << 0);
	
	// Reset Calibration
    ADC1->CR2 |= (1 << 3);

  // Wait until calibration is complete
  while((ADC1->CR2 & (1 << 3)) != 0);

  // Enable Calibration
  ADC1->CR2 |= (1 << 2);

  // Wait until calibration is complete
  while((ADC1->CR2 & (1 << 2)) != 0);
		
	NVIC->ISER[0] |= (1 << 18); // Enable ADC1_2_IRQHandler interrupt


}




