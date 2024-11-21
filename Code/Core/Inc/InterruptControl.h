/*
 * InterruptControl.h
 *
 *  Created on: Oct 3, 2024
 *      Author: Ethan
 */

#ifndef INTERRUPTCONTROL_H_
#define INTERRUPTCONTROL_H_

#include <stdint.h>
#include <stm32f4xx_hal.h>

#define EXTI0_IRQNum 6
//#define TIM2_IRQNum 28
//#define TIM5_IRQNum 50

#define active	1
#define not_active	0

#define enable	1
#define disable 0


//interrupt implementation
#define NVIC_ISER0_ADDR	0xE000E100
#define NVIC_ICER0_ADDR	0XE000E180
#define NVIC_ISPR0_ADDR 0XE000E200
#define NVIC_ICPR0_ADDR 0XE000E280
#define NVIC_IABR0_ADDR 0xE000E300
#define NVIC_IPR0_ADDR	0xE000E400

#define NVIC_ISER0	((volatile uint32_t*) NVIC_ISER0_ADDR)
#define NVIC_ICER0	((volatile uint32_t*) NVIC_ICER0_ADDR)
#define NVIC_ISPR0 	((volatile uint32_t*) NVIC_ISPR0_ADDR)
#define NVIC_ICPR0 	((volatile uint32_t*) NVIC_ICPR0_ADDR)
#define NVIC_IABR0 	((volatile uint32_t*) NVIC_IABR0_ADDR)
#define NVIC_IPR0	((volatile uint32_t*) NVIC_IPR0_ADDR))
///
#define NVIC_ISER1_ADDR	0xE000E104
#define NVIC_ICER1_ADDR	0XE000E184
#define NVIC_ISPR1_ADDR 0XE000E204
#define NVIC_ICPR1_ADDR 0XE000E284
#define NVIC_IABR1_ADDR 0xE000E304
#define NVIC_IPR1_ADDR	0xE000E404

#define NVIC_ISER1	((volatile uint32_t*) NVIC_ISER1_ADDR)
#define NVIC_ICER1	((volatile uint32_t*) NVIC_ICER1_ADDR)
#define NVIC_ISPR1 	((volatile uint32_t*) NVIC_ISPR1_ADDR)
#define NVIC_ICPR1 	((volatile uint32_t*) NVIC_ICPR1_ADDR)
#define NVIC_IABR1 	((volatile uint32_t*) NVIC_IABR1_ADDR)
#define NVIC_IPR1	((volatile uint32_t*) NVIC_IPR1_ADDR))
///
#define APB2_BASE_ADDRESS	0x40010000
#define SYSCFG_BASE_ADDR	(APB2_BASE_ADDRESS + 0x3800)
#define EXTI_BASE_ADDR		(APB2_BASE_ADDRESS + 0x3C00)

typedef struct
{
	volatile uint32_t	SYSCFG_MEMRMP;
	volatile uint32_t	SYSCFG_PMC;
	volatile uint32_t	SYSCFG_EXTI_ICRs[4];
	volatile uint32_t	SYSCFG_CMPCR;
}SYSCFG_RegDef_t;

typedef struct
{
	volatile uint32_t	EXTI_IMR;
	volatile uint32_t	EXTI_EMR;
	volatile uint32_t	EXTI_RTSR;
	volatile uint32_t	EXTI_FTSR;
	volatile uint32_t	EXTI_SWIER;
	volatile uint32_t	EXTI_PR;
}EXTI_RegDef_t;

//#define	SYSCFG				((SYSCFG_RegDef_t*)SYSCFG_BASE_ADDR)
//#define	EXTI				((EXTI_RegDef_t*)EXTI_BASE_ADDR)
#define SYSCFG_bitOffset	14

#define SYSCFG_CLK_ENABLE(SYSCFG_bitOffset)		(RCC->RCC_APB2ENR |= (1<<SYSCFG_bitOffset));
#define SYSCFG_CLK_DISABLE(SYSCFG_bitOffset)	(RCC->RCC_APB2ENR &= ~(1<<SYSCFG_bitOffset));
//////////////////////////////////

void NVIC_EnableIRQs(uint8_t IRQ_Num);
void NVIC_DisableIRQs(uint8_t IRQ_Num);
void NVIC_SetPendingIRQs(uint8_t IRQ_Num);
void NVIC_ClearPendingIRQs(uint8_t IRQ_Num);
void EXTI_ClearPendingBit(uint8_t pinNum);

void HAL_NVIC_EnableIRQ(IRQn_Type IRQn);
void HAL_NVIC_DisableIRQ(IRQn_Type IRQn);
void HAL_NVIC_SetPendingIRQ(IRQn_Type IRQn);
void HAL_NVIC_ClearPendingIRQ(IRQn_Type IRQn);
void HAL_EXTI_ClearPending(EXTI_HandleTypeDef *hexti, uint32_t edge);



#endif /* INTERRUPTCONTROL_H_ */
