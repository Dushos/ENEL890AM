#ifndef COMBINE_H
#define COMBINE_H


#include "stm32f10x.h"
#include <stdint.h>

#define startpoint 1000
#define max_point 1500

/*HEADER FILE FOR PWM */

	void stm32_TimerSetup (void);
	void Pwm_GpioSetup (void);
	void automatic(void);
	void manual(void);
	

	/*HEADER FILE FOR ADC */
	void ADC_Config(void);
	void ADC_GPIO_Init(void);
	void ADC1_2_IRQHandler(void);
	extern volatile uint16_t adc_value;
	extern volatile uint8_t adc_ready;
	extern volatile uint16_t setpoint; // default setpoint
	
	
	
	
	
	
	

#endif /* UART HEADER FILE */
