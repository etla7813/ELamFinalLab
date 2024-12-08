/*
 * RNG_Driver.h
 *
 *  Created on: Nov 21, 2024
 *      Author: Ethan
 */

#ifndef INC_RNG_DRIVER_H_
#define INC_RNG_DRIVER_H_

#include <stm32f4xx_hal.h>

void RNGInit();
uint32_t RNG_getVal();

#endif /* INC_RNG_DRIVER_H_ */
