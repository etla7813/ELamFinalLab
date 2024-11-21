/*
 * Button_Driver.h
 *
 *  Created on: Sep 26, 2024
 *      Author: Ethan
 */

#ifndef BUTTON_DRIVER_H_
#define BUTTON_DRIVER_H_

#include <stm32f4xx_hal.h>
#include <InterruptControl.h>

#define BUTTON_PORT	GPIOA
#define BUTTON_PIN	GPIO_PIN_0
#define BUTTON_PRESS 1
#define BUTTON_NOTPRESS 0

void	buttonInit();
void	button_clockEnable();
uint8_t button_checkPress();
//interrupt
void 	buttonInterruptMode();




#endif /* BUTTON_DRIVER_H_ */
