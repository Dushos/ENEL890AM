/**
   Initialize the timer TIM4.
*/
#include "minimal_regs.h"
#include "devices.h"

void stm32_TimerSetup (void) {

    RCC_APB1ENR |= 1u<<2;	// 1: enable clock for TIM4

   // TIM4_PSC = 1;     // 1 set prescaler
    //TIM4_ARR = 35999; // set auto-reload after 36,000 clks

    TIM4_CR1 = 0;     // reset command register 1
    TIM4_CR2 = 0;     // reset command register 2

    TIM4_PSC = 71; 
    TIM4_ARR = 19999;  // set auto-reload after 20,000 clks

    TIM4_CCR1  = 1500;       // 50%
    TIM4_CCR2  = 0;       // Phase 2 TIM4 CH2
    TIM4_CCR3  = 0;    //
    TIM4_CCR4  = 0;    //
    TIM4_CCMR1 |= 0x0060; // Set output compare mode to PWM mode 1: set bits 6 and 5 to 1
		TIM4_CCMR1 &= ~0x0010; // Clear bit 4 to select PWM mode 1
    TIM4_CCMR2 = 0;  // formerly 0x6060
		TIM4_CCER |= (1 << 0);  // Set CC2E bit capture/compare enable register
		TIM4_CCER &= ~(1 << 1); // Clear CC2P bit (default is active high)
    TIM4_SMCR  = 0;       // 0 set slave mode control register

    TIM4_CR1 = 1u<<2;    // 1: URS: Only counter overflow/underflow
			 // generates an update interrupt or DMA
			 // request if enabled.

    TIM4_CR2 = 0;        // 0x0 set command register 2

    TIM4_CR1 |= 1u<<0;   // 0: enable timer
}
