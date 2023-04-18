
#include "minimal_regs.h"
#include "combine.h"

void Pwm_GpioSetup (void) {
	/**
   Turn on GPIOB clock, configure PB9, PB8 as alt-function output.
*/
  
    RCC_APB2ENR |= 1u<<3;	// bit 3: IOPBEN=1, enable GPIOB clock
    
    GPIOB_CRL = 0;		// Clear bits 27:24 to reset the configuration of PB6
		GPIOB_CRL = (0xBu << 28); 		//bits 27:24: PB6, output mode, 50MHz, alt func push-pull
		
    
} // end of stm32_GpioSetup

void ADC_GPIO_Init(void) {
   
	 // enable GPIOC 
		RCC->APB2ENR = (1 << 4) ;
	
	//Set PC0 to input mode
	GPIOC->CRL = 0;
	GPIOC->CRL = 0x0 << 0 ;

}


