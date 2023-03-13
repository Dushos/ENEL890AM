#include "stm32f10x.h"
#include "uart_led.h"
#include <stdio.h>




int main(void){
    SystemInit();
    Uart2Config ();
    GPIO_Config();

    while(1){
        // check if data is available in USART buffer
        if(USART2->SR & USART_SR_RXNE){
            uint8_t data = UART2_GetChar(); // read the incoming data

            // perform actions based on the received data
            if(data == '1'){
                GPIOA->BSRR |= (1<<5); // turn the LED on
                UART2_SendString("LED is turned on.\n\r"); // send confirmation message
            }
            else if(data == '0'){
                GPIOA->BSRR |= 1<<(5 + 16); // turn the LED off
                UART2_SendString("LED is turned off.\n\r"); // send confirmation message
            }
            else if(data == 'a'){
                GPIOA->BSRR |= 0x3E0; // turn on all LEDs
                UART2_SendString("All LEDs are turned on.\n\r"); // send confirmation message
            }
            else if(data == 'b'){
                GPIOA->BRR |= 0xFFFF; // turn off all LEDs
                UART2_SendString("All LEDs are turned off.\n\r"); // send confirmation message
            }
            else if(data == 'c'){
                uint32_t ledState = (GPIOA->ODR & (1<<5)) ? 1 : 0; // query the state of LED2
                char buffer[50];
                sprintf(buffer, "The state of LED2 is %d.\n\r", ledState);
                UART2_SendString(buffer); // send the state of LED2
            }
            else if(data == 'd'){
                char buffer[50];
                sprintf(buffer, "The main source file was compiled on %s at %s.\n\r", __DATE__, __TIME__);
                UART2_SendString(buffer); // send the compile date and time
            }
            else if(data == 'e'){
                UART2_SendString("Command List:\n\r");
                UART2_SendString("1: Turn on LED2\n\r");
                UART2_SendString("0: Turn off LED2\n\r");
                UART2_SendString("a: Turn on all LEDs\n\r");
                UART2_SendString("b: Turn off all LEDs\n\r");
                UART2_SendString("c: Query the state of LED2\n\r");
                UART2_SendString("d: Print the compile date and time\n\r");
                UART2_SendString("e: Print the command list\n\r");
            }
            else{
                UART2_SendString("Invalid command. Type 'e' for the list of commands.\n\r"); // send error message
            }
        }
    }
}
