/*
 * LED_Driver.h
 *
 *  Created on: Sep 12, 2024
 *      Author: Ethan
 */

#ifndef LED_DRIVER_H_
#define LED_DRIVER_H_
#include <stm32f4xx_hal.h>

#define	greenLED	1
#define	redLED		0

#define active	1
#define not_active	0

#define enable	1
#define disable 0

void	LED_Init(uint8_t LED);
void 	toggleLED(uint8_t LED);
void	turnOffLED(uint8_t LED);
void	turnOnLED(uint8_t LED);

#endif /* LED_DRIVER_H_ */
