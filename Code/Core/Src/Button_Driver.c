/*
 * Button_Driver.c
 *
 *  Created on: Sep 26, 2024
 *      Author: Ethan
 */

#include <Button_Driver.h>

void buttonInit()
{
	GPIO_InitTypeDef* button = {0};

	button->Pin = BUTTON_PIN;
	button->Mode = GPIO_MODE_IT_RISING_FALLING;
	button->Speed = GPIO_SPEED_FREQ_HIGH;
	button->Pull = GPIO_NOPULL;
	button_clockEnable();
	__HAL_RCC_GPIOA_CLK_ENABLE();
}


void	button_clockEnable()
{
	__HAL_RCC_GPIOA_CLK_ENABLE();
}

uint8_t button_checkPress()
{
	if (HAL_GPIO_ReadPin(BUTTON_PORT, BUTTON_PIN) == BUTTON_PRESS)
		return BUTTON_PRESS;
	else
		return BUTTON_NOTPRESS;
}

void buttonInterruptMode()
{
	GPIO_InitTypeDef button = {0};

	button.Pin = BUTTON_PIN;
	button.Mode = GPIO_MODE_IT_RISING_FALLING;
	button.Speed = GPIO_SPEED_FREQ_HIGH;
	button.Pull = GPIO_NOPULL;
	button_clockEnable();
	HAL_GPIO_Init (GPIOA, &button);
	HAL_NVIC_EnableIRQ(EXTI0_IRQNum);
}
