#include <stm32f10x.h>
#include <stdint.h>
#include "FreeRTOS.h"
#include "task.h"
#include "freeRTOSConfig.h"
#include "uart_led.h"
#include "Delay_F103.h"
#include "combine.h"
#include "queue.h"



int main(void) {
    // Initialize PWM
    Pwm_GpioSetup();
    stm32_TimerSetup();

    // Initialize ADC
    ADC_GPIO_Init();
    ADC_Config();

    // Initilize uart
    SystemInit();
    TIM2_Config();
    Uart2Config();

    // Create the mode selection message queue
    modeQueueHandle = xQueueCreate(1, sizeof(char));

    
    // Create the mode task
    xTaskCreate(Mode_task, "Mode", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY + 1, &modeTaskHandle);

    // Create the user input task
    xTaskCreate(Cli_Task, "User Input", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY + 3, &cliTaskHandle);

    vTaskStartScheduler(); // start the scheduler

    while (1); // should never reach here
}
