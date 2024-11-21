/*
 * LED_Driver.c
 *
 *  Created on: Sep 12, 2024
 *      Author: Ethan
 */

#include <LED_Driver.h>

void LED_Init(uint8_t LED)
{
	GPIO_InitTypeDef* Green = {0};
	GPIO_InitTypeDef* Red = {0};

	switch(LED)
	{
	case greenLED:
		Green->Pin = GPIO_PIN_13;
		Green->Mode = GPIO_MODE_OUTPUT_OD;
		Green->Speed = GPIO_SPEED_FREQ_HIGH;
		Green->Pull = GPIO_NOPULL;
		__HAL_RCC_GPIOG_CLK_ENABLE();
		HAL_GPIO_Init (GPIOG, Green);
		break;
	case redLED:
		Red->Pin = GPIO_PIN_14;
		Red->Mode = GPIO_MODE_OUTPUT_OD;
		Red->Speed = GPIO_SPEED_FREQ_HIGH;
		Red->Pull = GPIO_NOPULL;
		__HAL_RCC_GPIOG_CLK_ENABLE();
		HAL_GPIO_Init (GPIOG, Red);
		break;
	default:
		break;
	}
}

void toggleLED(uint8_t LED)
{
	switch(LED)
	{
	case greenLED:
		HAL_GPIO_TogglePin(GPIOG, GPIO_PIN_13);
		break;
	case redLED:
		HAL_GPIO_TogglePin(GPIOG, GPIO_PIN_14);
		break;
	default:
		break;
	}
}

void turnOffLED(uint8_t LED)
{
	switch(LED)
	{
	case greenLED:
		HAL_GPIO_WritePin(GPIOG, GPIO_PIN_13, not_active);
		break;
	case redLED:
		HAL_GPIO_WritePin(GPIOG, GPIO_PIN_14, not_active);
		break;
	default:
		break;
	}
}

void turnOnLED(uint8_t LED)
{
	switch(LED)
	{
	case greenLED:
		HAL_GPIO_WritePin(GPIOG, GPIO_PIN_13, active);
		break;
	case redLED:
		HAL_GPIO_WritePin(GPIOG, GPIO_PIN_14, active);
		break;
	default:
		break;
	}
}
