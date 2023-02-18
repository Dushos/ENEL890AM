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


void arithmetic_operation_two(void){
	
	int16_t start_time;
  int16_t stop_time;
	int n_iterations = 10;
  int32_t a, b;
  int64_t c, d;
	
	struct struct8 {
  int32_t x[2], y[2];
  };
	struct struct8 struct8_1, struct8_2;
	
struct struct128 {
  int32_t x[16], y[16];
  };
	struct struct128 struct128_1, struct128_2;
	
struct struct1024 {
  int32_t x[256], y[256];
  };
	struct struct1024 struct1024_1, struct1024_2;
	
	
	int angle_deg;
  float angle_rad, sin_value, cos_value;

	
	// Add two random 32-bit integers
  start_time = timer_start();
  for (int i = 0; i < n_iterations; i++) {
    a = rand();
    b = rand();
    a = a + b;
	}
	stop_time = timer_stop(start_time);
	
	
	  // Add two random 64-bit integers
  start_time = timer_start();
  for (int i = 0; i < n_iterations; i++) {
    c = ((int64_t)rand() << 32) | rand();
    d = ((int64_t)rand() << 32) | rand();
    c = c + d;
  }
  stop_time = timer_stop(start_time);
	
	
	// Multiply two random 32-bit integers
  start_time = timer_start();
  for (int i = 0; i < n_iterations; i++) {
    a = rand();
    b = rand();
    a = a * b;
  }
  stop_time = timer_stop(start_time);
	
		
		// Multiply two random 64-bit integers
	start_time = timer_start();
	for (int i = 0; i < n_iterations; i++) {
		c = ((int64_t)rand() << 32) | rand();
		d = ((int64_t)rand() << 32) | rand();
		c = c * d;
	}
	stop_time = timer_stop(start_time);
	
		
		// Divide two random 32-bit integers
	start_time = timer_start();
	for (int i = 0; i < n_iterations; i++) {
		a = rand();
		b = rand();
		a = a / b;
	}
	stop_time = timer_stop(start_time);
	

		// Divide two random 64-bit integers
	start_time = timer_start();
	for (int i = 0; i < n_iterations; i++) {
		c = ((int64_t)rand() << 32) | rand();
		d = ((int64_t)rand() << 32) | rand();
		c = c / d;
	}
	stop_time = timer_stop(start_time);
	

 // copy an 8-byte struct using the assignment operator
	start_time = timer_start();
  for (int i = 0; i < n_iterations; i++) {
    for (int j = 0; j < 2; j++) {
      struct8_1.x[j] = rand();
      struct8_1.y[j] = rand();
    }
    struct8_2 = struct8_1;
  }
	stop_time = timer_stop(start_time);
	
  // copy a 128-byte struct using the assignment operator
	start_time = timer_start();
  for (int i = 0; i < n_iterations; i++) {
    for (int j = 0; j < 16; j++) {
      struct128_1.x[j] = rand();
      struct128_1.y[j] = rand();
    }
    struct128_2 = struct128_1;
  }
	stop_time = timer_stop(start_time);
	

  // copy a 1024-byte struct using the assignment operator
	start_time = timer_start();
  for (int i = 0; i < n_iterations; i++) {
    for (int j = 0; j < 256; j++) {
      struct1024_1.x[j] = rand();
      struct1024_1.y[j] = rand();
    }
    struct1024_2 = struct1024_1;
  }
	stop_time = timer_stop(start_time);

	
	// using sin and cos function
	start_time = timer_start();
	for (angle_deg = 0; angle_deg < 360; angle_deg++) {
    angle_rad = angle_deg * pi / 180.0;
    sin_value = sinf(angle_rad);
    cos_value = cosf(angle_rad);

}
	stop_time = timer_stop(start_time);



}

void timer_shutdown(void) {
  TIM2->CR1 &= ~(1<<0); /* DISABLE THE COUNTER */
}



 void External_Measurement(void){
	
	/* initialize the clock for GPIOA */
	RCC->APB2ENR |= (1<<2);

	/*CONFIGURE PIN5 on GPIOC*/
	GPIOA->CRL |= (	(1<<20) | (1<<21)	); 
	GPIOA->CRL &= ~(	(1<<22) |	(1<<23)	);
	
	while(1) {
		GPIOA->BSRR = (1<<5);
		for (int i = 0; i<=5000000; i++);
		GPIOA->BSRR = 1<<(5 + 16);
		for (int i = 0; i<=5000000; i++);
		
		
	} 
	
}

void init_usart(void) {
  /* Enable GPIOA and USART1 peripheral clocks */
  RCC->APB2ENR |= RCC_APB2ENR_IOPAEN | RCC_APB2ENR_USART1EN;

  /* Configure TX pin (PA9) as alternate function output */
  GPIOA->CRH &= ~(GPIO_CRH_MODE9 | GPIO_CRH_CNF9);
  GPIOA->CRH |= GPIO_CRH_MODE9_1 | GPIO_CRH_CNF9_1;

  /* Configure RX pin (PA10) as input with pull-up */
  GPIOA->CRH &= ~(GPIO_CRH_CNF10 | GPIO_CRH_MODE10);
  GPIOA->CRH |= GPIO_CRH_CNF10_1 | GPIO_CRH_MODE10;

  /* Configure USART1 with the following settings:
   * - 115200 baud rate
   * - 8 data bits
   * - 1 stop bit
   * - no parity
   * - no hardware flow control
   */
  USART1->BRR = SystemCoreClock / 115200;
  USART1->CR1 = USART_CR1_UE | USART_CR1_TE | USART_CR1_RE;
  USART1->CR2 = 0;
  USART1->CR3 = 0;
}


