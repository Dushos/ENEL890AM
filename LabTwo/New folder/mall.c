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
  
 
  TimeConfig();
  
  start_time = timer_start();
  arithmetic_operation();
	stop_time = timer_stop(start_time);
  
	
	
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


	

	timer_shutdown();

	
  
}
