/*
 * RNG_Driver.c
 *
 *  Created on: Nov 21, 2024
 *      Author: Ethan
 */

#include <RNG_Driver.h>

static RNG_HandleTypeDef RNG_1 = {0};

void RNG_Init()
{
	HAL_RNG_Init(&RNG_1);
}
uint32_t RNG_getVal()
{
	uint32_t rng_val = HAL_RNG_GetRandomNumber(&RNG_1);
	return rng_val;
}
