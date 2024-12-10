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

#define xgrid	24
#define ygrid	24

#define xstart2	xgrid*4
#define xstart1 xgrid*5

#define square	0
#define rect	1
#define s_shape	3
#define z_shape	4
#define	l_shape	5
#define j_shape	6
#define t_shape	7

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
void check_gameEnd();
void block_rotate();

void game_Run();


#endif /* INC_BLOCK_DRIVER_H_ */
