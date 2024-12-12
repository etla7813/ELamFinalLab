/*
 * Block_Driver.h
 *
 *  Created on: Dec 7, 2024
 *      Author: Ethan
 */

#ifndef INC_BLOCK_DRIVER_H_
#define INC_BLOCK_DRIVER_H_

#include <RNG_Driver.h>
#include <LCD_Driver.h>
#include <stdlib.h>

#define xgrid	24
#define ygrid	24

#define xstart2	xgrid*4
#define xstart1 xgrid*5

#define square	0
#define rect	1
#define s_shape	2
#define z_shape	3
#define	l_shape	4
#define j_shape	5
#define t_shape	6

void grid_Init();
void blockFall();
void spawn_square(int16_t x, int16_t y, uint16_t color);
void spawn_rect(int16_t x, int16_t y, uint16_t color);
void spawn_s(int16_t x, int16_t y, uint16_t color);
void spawn_z(int16_t x, int16_t y, uint16_t color);
void spawn_l(int16_t x, int16_t y, uint16_t color);
void spawn_j(int16_t x, int16_t y, uint16_t color);
void spawn_t(int16_t x, int16_t y, uint16_t color);

void spawn_block();
void block_fall();
uint16_t block_checkCollision();
void block_place();
void block_rotate();
void DrawBlock(uint16_t x, uint16_t y, uint16_t color);

uint16_t check_gameEnd();
void game_Run();
void game_End();


#endif /* INC_BLOCK_DRIVER_H_ */
