#include "stm32f10x.h"
#include "timer.h"
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>


int main(void) {
  int16_t start_time;
  int16_t stop_time;
  
 
  TimeConfig();
  init_usart();
	
	
  start_time = timer_start();
	arithmetic_operation();
	stop_time = timer_stop(start_time);
	
	start_time = timer_start();
	arithmetic_operation_two();
	stop_time = timer_stop(start_time);
	
	External_Measurement();
  
	
	while(1);
  
 
}
