/*
 * RNG_Driver.h
 *
 *  Created on: Nov 19, 2024
 *      Author: Ethan
 */

#ifndef INC_RNG_DRIVER_H_
#define INC_RNG_DRIVER_H_

#include <stm32f4xx_hal.h>

void RNG_Init();
void RNG_getVal();

//just for later
// __HAL_RCC_RNG_CLK_ENABLE()



#endif /* INC_RNG_DRIVER_H_ */
