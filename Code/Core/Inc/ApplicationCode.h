/*
 * ApplicationCode.h
 *
 *  Created on: Dec 30, 2023
 *      Author: Xavion
 */

#include "LCD_Driver.h"
#include "stm32f4xx_hal.h"

#include <stdio.h>
#include <Block_Driver.h>
#include <RNG_Driver.h>

void spawnBlock();
void spawnSquare();
void spawnRect();
void spawnS();
void spawnZ();


#ifndef INC_APPLICATIONCODE_H_
#define INC_APPLICATIONCODE_H_

void RNGInit();

void ApplicationInit(void);
void LCD_Visual_Demo(void);

#if (COMPILE_TOUCH_FUNCTIONS == 1) && (COMPILE_TOUCH_INTERRUPT_SUPPORT == 0)
void LCD_Touch_Polling_Demo(void);
#endif // (COMPILE_TOUCH_FUNCTIONS == 1) && (COMPILE_TOUCH_INTERRUPT_SUPPORT == 0)

#endif /* INC_APPLICATIONCODE_H_ */
