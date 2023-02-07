#include <stdint.h>
#include "stm32f103rb.h"


#define RCC_BASE 0x40021000
#define GPIOA_BASE 0x40010800
#define GPIOB_BASE 0x40010C00

#define LED2_PIN 5

typedef struct {
    volatile uint32_t CR;
    volatile uint32_t CFGR;
    volatile uint32_t CIR;
    volatile uint32_t APB2RSTR;
    volatile uint32_t APB1RSTR;
    volatile uint32_t AHBENR;
    volatile uint32_t APB2ENR;
    volatile uint32_t APB1ENR;
    volatile uint32_t BDCR;
    volatile uint32_t CSR;
} RCC_TypeDef;

typedef struct {
    volatile uint32_t CRL;
    volatile uint32_t CRH;
    volatile uint32_t IDR;
    volatile uint32_t ODR;
    volatile uint32_t BSRR;
    volatile uint32_t BRR;
    volatile uint32_t LCKR;
} GPIO_TypeDef;

#define RCC ((RCC_TypeDef *) RCC_BASE)
#define GPIOA ((GPIO_TypeDef *) GPIOA_BASE)
#define GPIOB ((GPIO_TypeDef *) GPIOB_BASE)

// Define the register addresses for GPIOA Pin 5
#define GPIOA_ODR (GPIOA_BASE + 0x0C)
#define GPIOA_BSRR (GPIOA_BASE + 0x10)

void driver_Open(void)
{
    // Enable clock for GPIOA peripheral
    RCC->APB2ENR |= (1 << 2);

    // Set Pin 5 as an output
    uint32_t reg = *((uint32_t *) GPIOA_CRL);
    reg &= ~(0xF << 20);
    reg |= (0x1 << 20);
    *((uint32_t *) GPIOA_CRL) = reg;
}

void driver_Close(void)
{
    // Disable clock for GPIOA peripheral
    RCC->APB2ENR &= ~(1 << 2);
}

void driver_Start(void)
{
    // Set the pin state to high
    *((uint32_t *) GPIOA_BSRR) = (1 << 5);
}

void driver_Stop(void)
{
    // Set the pin state to low
    *((uint32_t *) GPIOA_BSRR) = (1 << (5 + 16));
}

void driver_Update(void)
{
    // Toggle the pin state
    *((uint32_t *) GPIOA_ODR) ^= (1 << 5);
}

/*__interrupt void driver_Interrupt1(void)
{
}

__interrupt void driver_Interrupt2(void)
{
}  */
