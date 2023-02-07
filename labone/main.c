#include <stdio.h>
#include <stdint.h>
#include "stm32f103rb.h"




int main(void)
{
    driver_Open();
    while (1) {
        driver_Start();
        driver_Stop();
        driver_Update();
        
    }
    return 0;
}
