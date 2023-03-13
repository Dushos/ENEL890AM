/**
   Demonstration: generating PWM
 */

#include "devices.h"
#include "stm32f10x.h"
#include "uart_led.h"
#include "Delay_F103.h"
#include <stdio.h>
#include "minimal_regs.h"


int main (void){
    
		stm32_TimerSetup();
    stm32_GpioSetup();
		SystemInit ();
    TIM2_Config ();
    Uart2Config ();



while (1) {
    char input[16];
    int value;

    UART2_SendString("Enter a percentage (0-100) or a value between 600 and 2400: ");

    // Receive input from the user
    int i = 0;
    do {
        input[i] = UART2_GetChar();
        UART2_SendChar(input[i]);
        i++;
    } while (input[i-1] != '\r');  // wait until user presses Enter

    // Check if the input is a percentage or a raw value
    if (sscanf(input, "%d", &value) == 1) {
        if (value >= 0 && value <= 100) {
            handlePercentageInput(value);
        } else {
            handleRawInput(value);
        }
    } else {
        // handle invalid input
        UART2_SendString("\nError: Invalid input.\n");
    }
}

}



