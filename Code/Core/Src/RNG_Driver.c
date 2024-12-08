/*
 * RNG_Driver.c
 *
 *  Created on: Nov 21, 2024
 *      Author: Ethan
 */

#include <RNG_Driver.h>

static RNG_HandleTypeDef RNG_1 = {0};

void RNGInit()
{
	__HAL_RCC_RNG_CLK_ENABLE();
	RNG_1.Instance = RNG;
	HAL_RNG_Init(&RNG_1);
}
uint32_t RNG_getVal()
{
	uint32_t block_val = HAL_RNG_GetRandomNumber(&RNG_1);
	return block_val;
}
