

#include "stm32f10x.h"
#include <stdio.h>
#include <math.h>

#define pi 3.14159265358979323846

void TimeConfig(void);
int16_t timer_start(void);
int16_t timer_stop(int16_t start_time);
void arithmetic_operation(void);
void arithmetic_operation_two(void);
void timer_shutdown(void);
void External_Measurement(void);
void init_usart(void);
