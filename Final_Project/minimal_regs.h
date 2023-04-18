#ifndef MINIMAL_REGS_H
#define MINIMAL_REGS_H

/**
   Define useful registers for Lab4, which uses GPIOB, TIM4

*/
#include <stdint.h>

typedef uint32_t volatile * const reg32_t;
typedef uint16_t volatile * const reg16_t;

#define RCC_BASE              ( (uint32_t)0x40021000 )
#define RCC_APB1ENR           (* (reg32_t)(RCC_BASE + 0x1C) )
#define RCC_APB2ENR           (* (reg32_t)(RCC_BASE + 0x18) )

#define GPIOB_BASE            ( (uint32_t)0x40010C00 )
#define GPIOB_CRL             (* (reg32_t)(GPIOB_BASE + 0x00) )
#define GPIOB_CRH             (* (reg32_t)(GPIOB_BASE + 0x04) )
#define GPIOB_ODR             (* (reg32_t)(GPIOB_BASE + 0x0C) )
#define GPIOB_BSRR            (* (reg32_t)(GPIOB_BASE + 0x10) )
#define GPIOB_BRR             (* (reg32_t)(GPIOB_BASE + 0x14) )

#define TIM4_BASE             ( (uint32_t)0x40000800 )
#define TIM4_CR1              (* (reg16_t)(TIM4_BASE + 0x00) )
#define TIM4_CR2              (* (reg16_t)(TIM4_BASE + 0x04) )
#define TIM4_SMCR             (* (reg16_t)(TIM4_BASE + 0x08) )
#define TIM4_CCMR1            (* (reg16_t)(TIM4_BASE + 0x18) )
#define TIM4_CCMR2            (* (reg16_t)(TIM4_BASE + 0x1c) )
#define TIM4_CCER             (* (reg16_t)(TIM4_BASE + 0x20) )
#define TIM4_PSC              (* (reg16_t)(TIM4_BASE + 0x28) )
#define TIM4_ARR              (* (reg16_t)(TIM4_BASE + 0x2c) )
#define TIM4_CCR1             (* (reg16_t)(TIM4_BASE + 0x34) )
#define TIM4_CCR2             (* (reg16_t)(TIM4_BASE + 0x38) )
#define TIM4_CCR3             (* (reg16_t)(TIM4_BASE + 0x3c) )
#define TIM4_CCR4             (* (reg16_t)(TIM4_BASE + 0x40) )

#endif 
