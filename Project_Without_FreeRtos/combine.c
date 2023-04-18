
#include <stm32f10x.h>
#include "combine.h"
#include "uart_led.h"
#include "Delay_F103.h"
#include <stdio.h>




// Global variable to hold the converted ADC value
volatile uint16_t adc_value = 0;
volatile uint16_t setpoint = 0; // default setpoint

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
	
	  // Initialize PWM
    Pwm_GpioSetup();
    stm32_TimerSetup();

    // Initialize ADC
    ADC_GPIO_Init();
    ADC_Config();
	
		// Initilize uart
		SystemInit ();
    TIM2_Config ();
    Uart2Config ();


   while(1) {
        // Ask the user to select a mode
        UART2_SendString("Select a mode:\n1. Automatic\n2. Manual\n");

        // Receive input from the user
        char mode_input;
        do {
            mode_input = UART2_GetChar();
            UART2_SendChar(mode_input);
        } while (mode_input != '1' && mode_input != '2'); // wait until user enters a valid input

        // Handle the selected mode
        if (mode_input == '1') {
            automatic();
        } else if (mode_input == '2') {
            manual();
        }


					else {
						// error message for invalid input
						UART2_SendString("\nInvalid input. Please enter 1 or 2.\n");
					}
		}
}

