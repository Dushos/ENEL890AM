/**
   Initialize the timer TIM4.
*/
#include "minimal_regs.h"
#include "combine.h"


void stm32_TimerSetup (void) {

    RCC_APB1ENR |= 1u<<2;	// 1: enable clock for TIM4

   // TIM4_PSC = 1;     // 1 set prescaler
   // TIM4_ARR = 35999; // set auto-reload after 36,000 clks

    TIM4_CR1 = 0;     // reset command register 1
    TIM4_CR2 = 0;     // reset command register 2

    TIM4_PSC = 71; 
    TIM4_ARR = 19999;  // set auto-reload after 10,000 clks

    TIM4_CCR1  = 0;       // 0
    TIM4_CCR2  = 1000;       // 0
    TIM4_CCR3  = 0;    //
    TIM4_CCR4  = 0;    //
    TIM4_CCMR1 = 0x6060;       // 0
    TIM4_CCMR2 = 0;  // 0x6060
    TIM4_CCER |= (1 << 4);  // Set CC2E bit capture/compare enable register
		TIM4_CCER &= ~(1 << 5); // Clear CC2P bit (default is active high)
    TIM4_SMCR  = 0;       // 0 set slave mode control register

    TIM4_CR1 = 1u<<2;    // 1: URS: Only counter overflow/underflow
			 // generates an update interrupt or DMA
			 // request if enabled.

    TIM4_CR2 = 0;        // 0x0 set command register 2

    TIM4_CR1 |= 1u<<0;   // 0: enable timer
}
