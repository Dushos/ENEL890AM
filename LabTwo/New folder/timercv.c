#include "stm32f10x.h"
#include "timer.h"
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define pi 3.14159265358979323846

void TimeConfig(void) {
  RCC->APB1ENR |= (1<<0); /* Enable TIM2 clock */
	
  /* Setup prescaler*/
  TIM2->PSC |= (36-1); /* prescaler is +1 so we subtract 1*/
  TIM2->ARR = 0xffff ; /* max ARR value */
	
  /* enable the timer*/
  TIM2->CR1 |= (1<<0) ; /* ENABLES THE COUNTER*/
  while (!(TIM2->SR & (1<<0)));
	
}

/*start time*/
int16_t timer_start(void) {
  int16_t start_time = (int16_t)TIM2->CNT;
  return start_time;
}

/*stop time*/
int16_t timer_stop(int16_t start_time) {
  int16_t stop_time = (int16_t)TIM2->CNT;
  return (stop_time - start_time);
}

/*arithmetic operation */
	void arithmetic_operation(void) {
  int n_iterations = 11;
  double x, sin_x, term;
  
		
  for (int i = 0; i < 2; i++) {
    if (i == 0) {
      x = pi / 6;
    } else {
      x = 1000 * pi / 6;
    }

    sin_x = 0;
    term = x;
    for (int j = 1; j < n_iterations; j++) {
      sin_x += term;
      term = -term * x * x / ((2 * j + 1) * (2 * j));
    }
  }
}




void timer_shutdown(void) {
  TIM2->CR1 &= ~(1<<0); /* DISABLE THE COUNTER */
}
