#include <stm32f10x.h>
#include "adc.h"
#include "uart_main.h"
#include <stdio.h>
#include "Delay_F103.h"


// Global variable to hold the converted ADC value
volatile uint16_t adc_value = 0;

volatile uint8_t adc_ready = 0;

void ADC1_2_IRQHandler(void) {
    // Check if end-of-conversion occurred
    if (ADC1->SR & ADC_SR_EOC) {
        // Read the converted value and store it globally
        adc_value = ADC1->DR;
        // Set the flag to indicate a new value is ready
        adc_ready = 1;
    }
    // Clear the EOC bit in the SR register
    ADC1->SR &= ~(ADC_SR_EOC);
}


int main(void) {
	
	char adc_str[10];
    
		ADC_GPIO_Init();
    ADC_Config();
		SystemInit ();
    TIM2_Config ();
    Uart2Config ();
		
	
				 while(1){
        // Check if a new value is ready
        if (adc_ready) {
            // Send ADC value string over UART
            sprintf(adc_str, "%d", adc_value);
            UART2_SendString("ADC value: ");
            UART2_SendString(adc_str);
            UART2_SendString("\n");

            // Reset the flag
            adc_ready = 0;
        }

        // Start a conversion by setting the SWSTART bit
        ADC1->CR2 |= (1 << 22);

        // Delay for some time
        Delay_ms(1000);
    }
}

