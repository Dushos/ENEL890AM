
#include "stm32f10x.h"
#include "combine.h"
#include <stdio.h>
#include "uart_led.h"
#include <stdlib.h>


void automatic(void) {
    char adc_str[10];
    int duty_cycle = setpoint;
    char duty_cycle_str[10];
    char error_str[10];
    char setpoint_str[10];

   //setpoint = 1500;
					
					UART2_SendString("\nRecommended(1500); Enter desired setpoint: ");
					 // Receive input from the user
						int i = 0;
						char input[10];
						do {
								input[i] = UART2_GetChar();
								UART2_SendChar(input[i]);
								i++;
						} while (input[i-1] != '\r');  // wait until user presses Enter

						// Convert input to integer and set setpoint
						setpoint = atoi(input);
						UART2_SendString("\nSetpoint: ");
						UART2_SendString(input);
						UART2_SendString("\n");


							
						// Automatic mode
						while (1) {
				// Check if a new value is ready
				if (adc_ready) {
					// Send ADC value string over UART
					sprintf(adc_str, "%d", adc_value);
					UART2_SendString("ADC value: ");
					UART2_SendString(adc_str);
					UART2_SendString("\n");

					// Reset the flag
					adc_ready = 0;

					// Calculate the error between the setpoint and ADC value
					int error = setpoint - adc_value;

						
						if (abs(error >= 0)) {
								if (error > 0 && error < 100) {
										duty_cycle = 1256; // set PWM duty cycle to 1274
								}
								else if (error >= 100 && error <= 600) {
										duty_cycle = 1240; // set PWM duty cycle to 1272
								}
								else {
										duty_cycle = 1230; // set PWM duty cycle to drop the ball down when going out of range
								}
						}
						else {
								duty_cycle = 1276;
						}

						
							TIM4->CCR2 = duty_cycle;
						
			
					
					// Send duty cycle value over UART
					sprintf(duty_cycle_str, "%d", duty_cycle);
					UART2_SendString("Duty cycle: ");
					UART2_SendString(duty_cycle_str);
					UART2_SendString("\n");
					
					// Print the error
					sprintf(error_str, "%d", error);
					UART2_SendString("Error: ");
					UART2_SendString(error_str);
					UART2_SendString("\n");
					
						
						// Print the setpoint
					sprintf(setpoint_str, "%d", setpoint);
					UART2_SendString("setpoint: ");
					UART2_SendString(setpoint_str);
					UART2_SendString("\n");
				}

				
        // Start a conversion by setting the SWSTART bit
        ADC1->CR2 |= (1 << 22);
				
			}			
}

void manual(void){

					// Manual mode
	
				char duty_cycle_str[10];
				int duty_cycle;
					UART2_SendString("\nManual mode selected\n");
					UART2_SendString("Press A to increase duty cycle or L to decrease duty cycle or 0 to reset\n");
					duty_cycle = 1000; // initialize duty_cycle to 999
					while (1) {
							char input = UART2_GetChar();
							if (input == 'A') {
									duty_cycle += 1;
									if (duty_cycle > 1500) {
											duty_cycle = 1500;
									}
									TIM4->CCR2 = duty_cycle;
									sprintf(duty_cycle_str, "%d", duty_cycle);
									UART2_SendString("Duty cycle: ");
									UART2_SendString(duty_cycle_str);
									UART2_SendString("\n");
							}
							else if (input == 'L') {
									duty_cycle -= 1;
									if (duty_cycle < 1000) {
											duty_cycle = 1000;
									}
									sprintf(duty_cycle_str, "%d", duty_cycle);
									UART2_SendString("Duty cycle: ");
									UART2_SendString(duty_cycle_str);
									UART2_SendString("\n");
									TIM4->CCR2 = duty_cycle;
							}
							else if (input == '0') {
									 break;
								}
							else {
									UART2_SendString("Invalid key. Press + to increase duty cycle or - to decrease duty cycle\n");
							}
					}
}
