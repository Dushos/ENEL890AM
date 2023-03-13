/**
   Turn on GPIOB clock, configure PB9, PB8 as alt-function output.
*/
#include "minimal_regs.h"
#include "devices.h"
#include "stm32f10x.h"

void stm32_GpioSetup (void) {
  
  	
		// redone
		RCC_APB2ENR |= 1u<<3;	// bit 3: IOPBEN=1, enable GPIOB clock
		
		// Configure PB6 as TIM4_CH1 output
		GPIOB->CRL = 0;		// Clear bits 27:24 to reset the configuration of PB6
		GPIOB->CRL = (0xBu << 24); 		//bits 27:24: PB6, output mode, 50MHz, alt func push-pull
		
	
		

} // end of stm32_GpioSetup

