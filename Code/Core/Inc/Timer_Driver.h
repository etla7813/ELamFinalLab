/*
 * Timer_Driver.h
 *
 *  Created on: Oct 8, 2024
 *      Author: Ethan
 */

#ifndef TIMER_DRIVER_H_
#define TIMER_DRIVER_H_

#include <LED_Driver.h>
#include <stm32f4xx_hal.h>
#include <InterruptControl.h>

void timer_Init();
uint32_t timer_getTime();


#endif /* TIMER_DRIVER_H_ */
