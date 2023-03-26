ENSE 481
Lab 4 - Measuring Distance
Ping-Pong Ball Distance Measurement System

Introduction: This project involves building a system to measure the distance of a ping-pong ball as it travels through a tube using an infrared sensor. The system uses an STM32F103C8T6 microcontroller and an infrared sensor to capture the analog data of the ping-pong ball passing by the sensor. The system then converts the analog data to digital using an analog-to-digital converter (ADC) and calculates the distance of the ball based on the ADC reading.

System Requirements: To build this system, you will need the following materials:
* STM32F103C8T6 microcontroller board
* Infrared Sensor
* Ping-Pong Ball
* Ruler
* Jumper wires
* Breadboard
* USB Cable
* Computer

PHASE 1 - Setting up the ADC block
In this phase, the ADC block was setup to enable analog-to-digital conversions. The setup process was done with the following steps.
1. The breakout board schematic was consulted to determine how to interface the analog sensor to it.
2. The analog input pin used was PC0 on the processor. It was labeled as ANALOG1 that buffers to BUFF ANA1 on the breakout board's schematic and is connected to the J9 header, pin 1.
3. The peripheral clock for GPIOC (RCC APB2ENR) was enabled, and PC0 was set to input mode with a floating input (GPIOC CRL).
4. PC0 was connected to the first analog control block (ADC1) by enabling the clock (in an RCC register) for ADC1 (RCC APB2ENR).
5. The regular sequence registers were modified by setting the input channel into the SQ1 position. The analog input channel connected to PC0 was channel 10, so the first (and only) conversion was on channel 10. (ADC SQR3)
6. The sample time registers were set up by setting it up for 55.5 cycles for channel 10 (ADC SMPR1).
7. Scan mode and interrupt enable for EOC were enabled. External triggering was also enabled, and SWSTART was used as the external event select. The ADC was turned on (ADC CR1 and ADC CR2).
8. The bit for reset calibration was toggled high to start its initialization. The bit was monitored, and the team waited for it to go low again.
9. The bit for enabling calibration was toggled high and waited for it to return low again. The ADC block was then configured and ready.
10. In the main code, the bit in the ADC control register was set to trigger an ADC conversion of regular channels. The correct bit to use was based on the settings given above. The code set this, and when the conversion was done, the interrupt fired. The bit was automatically cleared in hardware, so there was no need to do that. The team found a way to let the main code know a conversion was done and reload this trigger bit so that the next conversion started.
By following these steps, the ADC block was properly set up.

PHASE 2 - Setting up the ADC interrupt to capture data
In this phase, the ADC interrupt was set up to capture data from the ADC block. The following steps were taken:
1. After the ADC block was initialized in Phase 1, a flag was set in the main code to indicate when a new value is ready for processing.
2. The correct bit in the NVIC registers was enabled to allow the interrupt to trigger a hardware vector jump when triggered. The ADC1_2_IRQHandler was used and its position was found in table 62 of the reference manual. The correct bit was then set in the NVIC ISER[x] register.
3. An ISR (Interrupt Service Routine) function was created in the main code file and named "void ADC1_2_IRQHandler(void) {}"
4. To ensure that the end of conversion (EOC) has occurred, the SR register was checked. However, since we only have one interrupt (ADC1) firing, this step was optional.
5. To get the converted value, the DR register was read and the value was stored globally so that the main code could access it later.

PHASE 3 - Calibrate the IR sensor
In Phase 3, the IR sensor was calibrated. The following steps were followed:
1. To get the converted value, the DR register was read and the value was stored globally so that the main code could access it later.
2. Configured the software to continually display the ADC output so that the distance readings can be observed.
3. Made a note of the ID number (1 through 6) of the ping-pong tube assembly used.
4. Removed the top fan/funnel assembly from the ping-pong ball controller with gentle wiggling and tip the assembly on its side so that the funnel does not put undue strain on the connecting wires. Insert a meter stick with a white piece of paper taped to the end.
5. Created a table of ADC readings versus actual distance (as measured with the meter stick). 
6. Constructed a corresponding plot of volts versus distance. The plot of Voltage versus Distance was done using tube 6 by Usheoritse Itsekiri with student id 200476234 on 21st March 2023.


