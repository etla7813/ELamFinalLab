/*
 * InterruptControl.c
 *
 *  Created on: Oct 3, 2024
 *      Author: Ethan
 */

#include <InterruptControl.h>
#include <stm32f4xx_hal.h>

void NVIC_EnableIRQs(uint8_t IRQ_Num)
{
	uint32_t IRQComp = 32;
	if(IRQ_Num < IRQComp)
		*NVIC_ISER0 |= (1 << IRQ_Num);
	if(IRQ_Num >= IRQComp)
		*NVIC_ISER0 |= (1 << (IRQ_Num%32));
}

void NVIC_DisableIRQs(uint8_t IRQ_Num)
{
	uint32_t IRQComp = 32;
	if(IRQ_Num < IRQComp)
		*NVIC_ICER0 |= (1 << IRQ_Num);
	if(IRQ_Num >= IRQComp)
		*NVIC_ICER0 |= (1 << IRQ_Num%32);
}

void NVIC_SetPendingIRQs(uint8_t IRQ_Num)
{
	uint32_t IRQComp = 32;
	if(IRQ_Num < IRQComp)
			*NVIC_ISPR0 |= (1 << IRQ_Num);
	if(IRQ_Num >= IRQComp)
			*NVIC_ISPR0 |= (1 << IRQ_Num%32);
}
void NVIC_ClearPendingIRQs(uint8_t IRQ_Num)
{
	uint32_t IRQComp = 32;
	if(IRQ_Num < IRQComp)
			*NVIC_ICPR0 |= (1 << IRQ_Num);
	if(IRQ_Num >= IRQComp)
			*NVIC_ICPR0 |= (1 << IRQ_Num%32);
}
void EXTI_ClearPendingBit(uint8_t pinNum)
{
	EXTI->PR |= (1 << pinNum);
}


