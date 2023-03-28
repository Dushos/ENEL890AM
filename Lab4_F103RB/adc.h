#ifndef ADC_H
#define ADC_H

#include <stdint.h>

void ADC_GPIO_Init(void);
void ADC_Config(void);
void ADC1_2_IRQHandler(void);
extern volatile uint16_t adc_value;
extern volatile uint8_t adc_ready;

#endif
