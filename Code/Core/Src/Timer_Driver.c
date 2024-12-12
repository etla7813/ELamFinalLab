/*
 * Timer_Driver.c
 *
 *  Created on: Oct 8, 2024
 *      Author: Ethan
 */

#include <Timer_Driver.h>

TIM_HandleTypeDef Timer2 = {0};
void timer_Init()
{
	Timer2.Instance = TIM2;
	Timer2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
	Timer2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	Timer2.Init.CounterMode = TIM_COUNTERMODE_UP;
	Timer2.Init.Period = 2000000;
	Timer2.Init.Prescaler = 31249;
	Timer2.Init.RepetitionCounter = 0;

	HAL_TIM_Base_Init(&Timer2);
	__HAL_TIM_ENABLE(&Timer2);
}

uint32_t timer_getTime()
{
	uint32_t time = __HAL_TIM_GET_COUNTER(&Timer2) / 200;
	return time;
}
