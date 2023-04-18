#include <stm32f10x.h>
#include <stdint.h>
#include "FreeRTOS.h"
#include "task.h"
#include "freeRTOSConfig.h"
#include "uart_led.h"
#include "Delay_F103.h"
#include "combine.h"
#include "queue.h"


// Global variable to hold the converted ADC value
volatile uint16_t adc_value = 0;
volatile uint16_t setpoint = 0; // default setpoint
volatile uint8_t adc_ready = 0;

TaskHandle_t modeTaskHandle = NULL;
TaskHandle_t cliTaskHandle = NULL;

QueueHandle_t modeQueueHandle = NULL;

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


void Mode_task(void *pvParameters) {
    char mode_input;
    while (1) {
        xQueueReceive(modeQueueHandle, &mode_input, portMAX_DELAY);
        if (mode_input == '1') {
            automatic();
        } else {
            manual();
        }
    }
}


void Cli_Task(void *pvParameters) {
    // Ask the user to select a mode
    UART2_SendString("Select a mode:\n1. Automatic\n2. Manual\n");

    // Receive input from the user
    char mode_input = '\0';
    while (mode_input != '1' && mode_input != '2') {
        taskYIELD(); // allow other tasks to run while waiting for input
        mode_input = UART2_GetChar();
        
        if (mode_input != '1' && mode_input != '2') {
            UART2_SendString("Invalid input. Please enter 1 or 2.\n");
        }
    }

    // Send the selected mode to the queue
    xQueueSend(modeQueueHandle, &mode_input, portMAX_DELAY);

    // Notify that mode selection is complete
    xTaskNotifyGive(cliTaskHandle);

    while (1) {
        vTaskDelay(pdMS_TO_TICKS(100)); // delay to allow other tasks to run
    }
}

