/*
 * Block_Driver.c
 *
 *  Created on: Dec 7, 2024
 *      Author: Ethan
 */


#include <Block_Driver.h>

int board[10][8] = {
			{0, 0, 0, 0, 0, 0, 0, 0},
			{0, 0, 0, 0, 0, 0, 0, 0},
			{0, 0, 0, 0, 0, 0, 0, 0},
			{0, 0, 0, 0, 0, 0, 0, 0},
			{0, 0, 0, 0, 0, 0, 0, 0},
			{0, 0, 0, 0, 0, 0, 0, 0},
			{0, 0, 0, 0, 0, 0, 0, 0},
			{0, 0, 0, 0, 0, 0, 0, 0},
			{0, 0, 0, 0, 0, 0, 0, 0},
			{0, 0, 0, 0, 0, 0, 0, 0}
	};
int game[10][8] = {
			{0, 0, 0, 0, 0, 0, 0, 0},
			{0, 0, 0, 0, 0, 0, 0, 0},
			{0, 0, 0, 0, 0, 0, 0, 0},
			{0, 0, 0, 0, 0, 0, 0, 0},
			{0, 0, 0, 0, 0, 0, 0, 0},
			{0, 0, 0, 0, 0, 0, 0, 0},
			{0, 0, 0, 0, 0, 0, 0, 0},
			{0, 0, 0, 0, 0, 0, 0, 0},
			{0, 0, 0, 0, 0, 0, 0, 0},
			{0, 0, 0, 0, 0, 0, 0, 0}
		};
//there are 4 blocks per object, so im gonna mark where they are
uint16_t x1_pos=0;;
uint16_t y1_pos=0;

uint16_t x2_pos=0;
uint16_t y2_pos=0;

uint16_t x3_pos=0;
uint16_t y3_pos=0;

uint16_t x4_pos=0;
uint16_t y4_pos=0;

uint16_t rotation=0;

uint16_t time_elapsed=0;

void spawn_square(int16_t x, int16_t y, uint16_t color)
{
	//block 1
	for(uint16_t i = x; i < x + xgrid ; i++)
	{
		LCD_Draw_Vertical_Line(i, y, ygrid, color);
	}
	LCD_Draw_Vertical_Line(x,y,ygrid, LCD_COLOR_WHITE);
	LCD_Draw_Horizontal_Line(x,y,xgrid, LCD_COLOR_WHITE);
	//block 2
	for(uint16_t i = x+xgrid; i < x + 2*xgrid ; i++)
	{
		LCD_Draw_Vertical_Line(i, y, ygrid, color);
	}
	LCD_Draw_Vertical_Line(x+xgrid,y,ygrid, LCD_COLOR_WHITE);
	LCD_Draw_Horizontal_Line(x+xgrid,y,xgrid, LCD_COLOR_WHITE);
	//block 3
	for(uint16_t i = x; i < x + xgrid ; i++)
	{
		LCD_Draw_Vertical_Line(i, y+ygrid, ygrid, color);
	}
	LCD_Draw_Vertical_Line(x,y+ygrid,ygrid, LCD_COLOR_WHITE);
	LCD_Draw_Horizontal_Line(x,y+ygrid,xgrid, LCD_COLOR_WHITE);

	//block 4
	for(uint16_t i = x+xgrid; i < x + 2*xgrid ; i++)
	{
		LCD_Draw_Vertical_Line(i, y+ygrid, ygrid, color);
	}
	LCD_Draw_Vertical_Line(x+xgrid,y+ygrid,ygrid, LCD_COLOR_WHITE);
	LCD_Draw_Horizontal_Line(x+xgrid,y+ygrid,xgrid, LCD_COLOR_WHITE);
}
void spawn_rect(int16_t x, int16_t y, uint16_t color)
{
	for(uint16_t i = x; i < x + xgrid ; i++)
	{
		LCD_Draw_Vertical_Line(i, y, ygrid*4, color);
	}
	LCD_Draw_Vertical_Line(x,y, ygrid*4, LCD_COLOR_WHITE);
	LCD_Draw_Horizontal_Line(x,y+ygrid,xgrid, LCD_COLOR_WHITE);
	LCD_Draw_Horizontal_Line(x,y+ygrid*2,xgrid, LCD_COLOR_WHITE);
	LCD_Draw_Horizontal_Line(x,y+ygrid*3,xgrid, LCD_COLOR_WHITE);
}
void spawn_s(int16_t x, int16_t y, uint16_t color)
{
	//block 1 & 2
	for(uint16_t i = x; i < x + 2*xgrid ; i++)
	{
		LCD_Draw_Vertical_Line(i, y, ygrid, color);
	}
	LCD_Draw_Vertical_Line(x,y,ygrid, LCD_COLOR_WHITE);
	LCD_Draw_Horizontal_Line(x,y,xgrid, LCD_COLOR_WHITE);
	LCD_Draw_Vertical_Line(x+xgrid,y,ygrid, LCD_COLOR_WHITE);
	LCD_Draw_Horizontal_Line(x+xgrid,y,xgrid, LCD_COLOR_WHITE);
	//block 3 & 4
	for(int16_t i = x-xgrid; i < x + xgrid ; i++)
	{
		LCD_Draw_Vertical_Line(i, y+ygrid, ygrid, color);
	}
	LCD_Draw_Vertical_Line(x-xgrid,y+ygrid,ygrid, LCD_COLOR_WHITE);
	LCD_Draw_Horizontal_Line(x-xgrid,y+ygrid,xgrid, LCD_COLOR_WHITE);
	LCD_Draw_Vertical_Line(x,y+ygrid,ygrid, LCD_COLOR_WHITE);
	LCD_Draw_Horizontal_Line(x,y+ygrid,xgrid, LCD_COLOR_WHITE);
	//update grid
}
void spawn_z(int16_t x, int16_t y, uint16_t color)
{
    // Block 1 & 2
    for (uint16_t i = x; i < x + 2 * xgrid; i++) {
        LCD_Draw_Vertical_Line(i, y, ygrid, color); // Top horizontal line
    }
    LCD_Draw_Vertical_Line(x, y, ygrid, LCD_COLOR_WHITE);
    LCD_Draw_Horizontal_Line(x, y, xgrid, LCD_COLOR_WHITE);
    LCD_Draw_Vertical_Line(x + xgrid, y, ygrid, LCD_COLOR_WHITE);
    LCD_Draw_Horizontal_Line(x + xgrid, y, xgrid, LCD_COLOR_WHITE);

    // Block 3 & 4
    for (uint16_t i = x + xgrid; i < x + 3 * xgrid; i++) {
        LCD_Draw_Vertical_Line(i, y + ygrid, ygrid, color); // Bottom horizontal line
    }
    LCD_Draw_Vertical_Line(x + xgrid, y + ygrid, ygrid, LCD_COLOR_WHITE);
    LCD_Draw_Horizontal_Line(x + xgrid, y + ygrid, xgrid, LCD_COLOR_WHITE);
    LCD_Draw_Vertical_Line(x + 2 * xgrid, y + ygrid, ygrid, LCD_COLOR_WHITE);
    LCD_Draw_Horizontal_Line(x + 2 * xgrid, y + ygrid, xgrid, LCD_COLOR_WHITE);
}
void spawn_l(int16_t x, int16_t y, uint16_t color)
{
    // Block 1 & 2 (Vertical line)
    for (uint16_t i = y; i < y + 3 * ygrid; i++) {
        LCD_Draw_Horizontal_Line(x, i, xgrid, color); // Vertical part of the "J"
    }
    LCD_Draw_Vertical_Line(x, y, ygrid, LCD_COLOR_WHITE);
    LCD_Draw_Vertical_Line(x, y + ygrid, ygrid, LCD_COLOR_WHITE);
    LCD_Draw_Horizontal_Line(x, y, xgrid, LCD_COLOR_WHITE);
    LCD_Draw_Horizontal_Line(x, y + ygrid, xgrid, LCD_COLOR_WHITE);

    // Block 3 (Bottom horizontal line, to the left)
    for (uint16_t i = x; i < x + 2*xgrid; i++) {
        LCD_Draw_Vertical_Line(i, y + 2 * ygrid, ygrid, color); // Bottom part of the "J"
    }
    LCD_Draw_Vertical_Line(x - xgrid, y + 2 * ygrid, ygrid, LCD_COLOR_WHITE);
    LCD_Draw_Horizontal_Line(x - xgrid, y + 2 * ygrid, xgrid, LCD_COLOR_WHITE);
    LCD_Draw_Horizontal_Line(x, y + 2 * ygrid, xgrid, LCD_COLOR_WHITE);
    LCD_Draw_Vertical_Line(x+xgrid, y+2*ygrid, xgrid, LCD_COLOR_WHITE);
}
void spawn_j(int16_t x, int16_t y, uint16_t color)
{
    // Block 1 & 2 (Vertical line)
    for (uint16_t i = y; i < y + 3 * ygrid; i++) {
        LCD_Draw_Horizontal_Line(x, i, xgrid, color); // Vertical part of the "J"
    }
    LCD_Draw_Vertical_Line(x, y, ygrid, LCD_COLOR_WHITE);
    LCD_Draw_Vertical_Line(x, y + ygrid, ygrid, LCD_COLOR_WHITE);
    LCD_Draw_Horizontal_Line(x, y, xgrid, LCD_COLOR_WHITE);
    LCD_Draw_Horizontal_Line(x, y + ygrid, xgrid, LCD_COLOR_WHITE);

    // Block 3 (Bottom horizontal line, to the left)
    for (uint16_t i = x - xgrid; i < x; i++) {
        LCD_Draw_Vertical_Line(i, y + 2 * ygrid, ygrid, color); // Bottom part of the "J"
    }
    LCD_Draw_Vertical_Line(x - xgrid, y + 2 * ygrid, ygrid, LCD_COLOR_WHITE);
    LCD_Draw_Horizontal_Line(x - xgrid, y + 2 * ygrid, xgrid, LCD_COLOR_WHITE);
    LCD_Draw_Horizontal_Line(x, y + 2 * ygrid, xgrid, LCD_COLOR_WHITE);
    LCD_Draw_Vertical_Line(x, y+2*ygrid, xgrid, LCD_COLOR_WHITE);
}
void spawn_t(int16_t x, int16_t y, uint16_t color)
{
    // Block 1, 2, and 3 (Top horizontal line)
    for (uint16_t i = x; i < x + 3 * xgrid; i++) {
        LCD_Draw_Vertical_Line(i, y, ygrid, color); // Top horizontal line
    }
    LCD_Draw_Vertical_Line(x, y, ygrid, LCD_COLOR_WHITE);
    LCD_Draw_Horizontal_Line(x, y, xgrid, LCD_COLOR_WHITE);
    LCD_Draw_Vertical_Line(x + xgrid, y, ygrid, LCD_COLOR_WHITE);
    LCD_Draw_Horizontal_Line(x + xgrid, y, xgrid, LCD_COLOR_WHITE);
    LCD_Draw_Vertical_Line(x + 2 * xgrid, y, ygrid, LCD_COLOR_WHITE);
    LCD_Draw_Horizontal_Line(x + 2 * xgrid, y, xgrid, LCD_COLOR_WHITE);

    // Block 4 (Vertical middle block)
    for (uint16_t i = y; i < y + ygrid; i++) {
        LCD_Draw_Horizontal_Line(x + xgrid, i, xgrid, color); // Vertical middle block
    }
    LCD_Draw_Vertical_Line(x + xgrid, y, ygrid, LCD_COLOR_WHITE);
    LCD_Draw_Horizontal_Line(x + xgrid, y, xgrid, LCD_COLOR_WHITE);
    LCD_Draw_Horizontal_Line(x + xgrid, y + ygrid, xgrid, LCD_COLOR_WHITE);
}

uint16_t block;
void spawn_block()
{
	block = RNG_getVal() % 7;
	if(block == square)
	{
		spawn_square(xstart2, 0, LCD_COLOR_YELLOW);
		//update grid
		x1_pos =4;
		y1_pos =0;
		x2_pos=5;
		y2_pos=0;
		x3_pos=4;
		y3_pos=1;
		x4_pos=5;
		y4_pos=1;

		game[y1_pos][x1_pos] = 1;
		game[y2_pos][x2_pos] = 1;
		game[y3_pos][x3_pos] = 1;
		game[y4_pos][x4_pos] = 1;
	}
	else if (block == rect)
	{
		spawn_rect(xstart2, 0, LCD_COLOR_BLUE);
		//update grid
		x1_pos =4;
		y1_pos =0;
		x2_pos=4;
		y2_pos=1;
		x3_pos=4;
		y3_pos=2;
		x4_pos=4;
		y4_pos=3;

		game[y1_pos][x1_pos] = 1;
		game[y2_pos][x2_pos] = 1;
		game[y3_pos][x3_pos] = 1;
		game[y4_pos][x4_pos] = 1;
	}
	else if (block == s_shape)
	{
		spawn_s(xstart2, 0, LCD_COLOR_RED);
		//update grid
		x1_pos =4;
		y1_pos =0;
		x2_pos=5;
		y2_pos=0;
		x3_pos=4;
		y3_pos=1;
		x4_pos=3;
		y4_pos=1;

		game[y1_pos][x1_pos] = 1;
		game[y2_pos][x2_pos] = 1;
		game[y3_pos][x3_pos] = 1;
		game[y4_pos][x4_pos] = 1;
	}
	else if (block == z_shape)
	{
		spawn_z(xstart2, 0, LCD_COLOR_GREEN);
		//update grid
		x1_pos =4;
		y1_pos =0;
		x2_pos=5;
		y2_pos=0;
		x3_pos=5;
		y3_pos=1;
		x4_pos=6;
		y4_pos=1;

		game[y1_pos][x1_pos] = 1;
		game[y2_pos][x2_pos] = 1;
		game[y3_pos][x3_pos] = 1;
		game[y4_pos][x4_pos] = 1;
	}
	else if (block == l_shape)
	{
		spawn_l(xstart2, 0, LCD_COLOR_CYAN);
	    //update grid
		x1_pos =4;
		y1_pos =0;
		x2_pos=4;
		y2_pos=1;
		x3_pos=4;
		y3_pos=2;
		x4_pos=5;
		y4_pos=2;

		game[y1_pos][x1_pos] = 1;
		game[y2_pos][x2_pos] = 1;
		game[y3_pos][x3_pos] = 1;
		game[y4_pos][x4_pos] = 1;
	}
	else if (block == j_shape)
	{
		spawn_j(xstart2, 0, LCD_COLOR_MAGENTA);
	    //update grid
		x1_pos =4;
		y1_pos =0;
		x2_pos=4;
		y2_pos=1;
		x3_pos=4;
		y3_pos=2;
		x4_pos=3;
		y4_pos=2;

		game[y1_pos][x1_pos] = 1;
		game[y2_pos][x2_pos] = 1;
		game[y3_pos][x3_pos] = 1;
		game[y4_pos][x4_pos] = 1;
	}
	else if (block == t_shape)
	{
		spawn_t(xstart2, 0, LCD_COLOR_BLUE2);
	    //update grid
		x1_pos =4;
		y1_pos =0;
		x2_pos=5;
		y2_pos=0;
		x3_pos=6;
		y3_pos=0;
		x4_pos=5;
		y4_pos=1;

		game[y1_pos][x1_pos] = 1;
		game[y2_pos][x2_pos] = 1;
		game[y3_pos][x3_pos] = 1;
		game[y4_pos][x4_pos] = 1;
	}
	else
	{
		spawn_l(xstart2, 0, LCD_COLOR_CYAN);
	}
}

uint16_t block_checkCollision()
{
	if(board[y1_pos + 1][x1_pos] == 1 || y1_pos == 10)
	{
		printf("collision");
		return 1;
	}
	else if(board[y2_pos + 1][x2_pos] == 1 || y2_pos == 10)
	{
		printf("collision");
		return 1;
	}
	else if(board[y3_pos + 1][x3_pos] == 1 || y3_pos == 10)
	{
		printf("collision");
		return 1;
	}
	else if(board[y4_pos + 1][x4_pos] == 1 || y4_pos == 10)
	{
		printf("collision");
		return 1;
	}
	else return 0;
}

void block_place()
{
	board[y1_pos][x1_pos] = game[y1_pos][x1_pos];
	board[y2_pos][x2_pos] = game[y2_pos][x2_pos];
	board[y3_pos][x3_pos] = game[y3_pos][x3_pos];
	board[y4_pos][x1_pos] = game[y4_pos][x1_pos];
	x1_pos = 0; x2_pos = 0; x3_pos = 0; x4_pos = 0;
	y1_pos = 0; y2_pos = 0; y3_pos = 0; y4_pos = 0;
}

void block_fall()
{
	extern uint16_t block;
	extern uint16_t y1_pos; extern uint16_t y2_pos; extern uint16_t y3_pos; extern uint16_t y4_pos;
	extern uint16_t x1_pos; extern uint16_t x2_pos; extern uint16_t x3_pos; extern uint16_t x4_pos;
	if(block==square)
	{
		while(block_checkCollision() == 0)
		{
			HAL_Delay(1000);
			time_elapsed++;

			int16_t x1 = 24*x1_pos; int16_t x2 =24*x2_pos;
			int16_t x3 = 24*x3_pos; int16_t x4 =24*x4_pos;
			int16_t y1 = 24*y1_pos; int16_t y2 =24*y2_pos;
			int16_t y3 = 24*y3_pos; int16_t y4 =24*y4_pos;
			spawn_square(x1,y1,LCD_COLOR_BLACK);

			y1 = y1+24; y2 = y2+24; y3 = y3+24; y4 = y4+24;
			spawn_square(x1,y1,LCD_COLOR_YELLOW);
			game[y2_pos][x2_pos] = 0;
			game[y2_pos][x2_pos] = 0;
			game[y3_pos][x3_pos] = 0;
			game[y4_pos][x4_pos] = 0;

			game[y1_pos+1][x1_pos] =1;
			game[y2_pos+1][x2_pos] =1;
			game[y3_pos+1][x3_pos] =1;
			game[y4_pos+1][x4_pos] =1;

			y1_pos++; y2_pos++; y3_pos++; y4_pos++;
		}
		block_place();
	}
	else if(block==rect)
	{
		while(block_checkCollision() == 0)
		{
			HAL_Delay(1000);
			time_elapsed++;

			int16_t x1 = 24*x1_pos; int16_t x2 =24*x2_pos;
			int16_t x3 = 24*x3_pos; int16_t x4 =24*x4_pos;
			int16_t y1 = 24*y1_pos; int16_t y2 =24*y2_pos;
			int16_t y3 = 24*y3_pos; int16_t y4 =24*y4_pos;
			spawn_rect(x1,y1,LCD_COLOR_BLACK);

			y1 = y1+24; y2 = y2+24; y3 = y3+24; y4 = y4+24;
			spawn_rect(x1,y1,LCD_COLOR_BLUE);
			game[y2_pos][x2_pos] = 0;
			game[y2_pos][x2_pos] = 0;
			game[y3_pos][x3_pos] = 0;
			game[y4_pos][x4_pos] = 0;

			game[y1_pos+1][x1_pos] =1;
			game[y2_pos+1][x2_pos] =1;
			game[y3_pos+1][x3_pos] =1;
			game[y4_pos+1][x4_pos] =1;
			y1_pos++; y2_pos++; y3_pos++; y4_pos++;
		}
		block_place();
	}
	else if(block == s_shape)
	{
		while(block_checkCollision() == 0)
		{
			HAL_Delay(1000);
			time_elapsed++;

			int16_t x1 = 24*x1_pos; int16_t x2 =24*x2_pos;
			int16_t x3 = 24*x3_pos; int16_t x4 =24*x4_pos;
			int16_t y1 = 24*y1_pos; int16_t y2 =24*y2_pos;
			int16_t y3 = 24*y3_pos; int16_t y4 =24*y4_pos;
			spawn_s(x1,y1,LCD_COLOR_BLACK);

			y1 = y1+24; y2 = y2+24; y3 = y3+24; y4 = y4+24;
			spawn_s(x1,y1,LCD_COLOR_RED);
			game[y2_pos][x2_pos] = 0;
			game[y2_pos][x2_pos] = 0;
			game[y3_pos][x3_pos] = 0;
			game[y4_pos][x4_pos] = 0;

			game[y1_pos+1][x1_pos] =1;
			game[y2_pos+1][x2_pos] =1;
			game[y3_pos+1][x3_pos] =1;
			game[y4_pos+1][x4_pos] =1;
			y1_pos++; y2_pos++; y3_pos++; y4_pos++;
		}
		block_place();
	}
	else if(block == z_shape)
	{
		while(block_checkCollision() == 0)
		{
			HAL_Delay(1000);
			time_elapsed++;

			int16_t x1 = 24*x1_pos; int16_t x2 =24*x2_pos;
			int16_t x3 = 24*x3_pos; int16_t x4 =24*x4_pos;
			int16_t y1 = 24*y1_pos; int16_t y2 =24*y2_pos;
			int16_t y3 = 24*y3_pos; int16_t y4 =24*y4_pos;
			spawn_z(x1,y1,LCD_COLOR_BLACK);

			y1 = y1+24; y2 = y2+24; y3 = y3+24; y4 = y4+24;
			spawn_z(x1,y1,LCD_COLOR_GREEN);
			game[y2_pos][x2_pos] = 0;
			game[y2_pos][x2_pos] = 0;
			game[y3_pos][x3_pos] = 0;
			game[y4_pos][x4_pos] = 0;

			game[y1_pos+1][x1_pos] =1;
			game[y2_pos+1][x2_pos] =1;
			game[y3_pos+1][x3_pos] =1;
			game[y4_pos+1][x4_pos] =1;
			y1_pos++; y2_pos++; y3_pos++; y4_pos++;
		}
		block_place();
	}
	else if(block == l_shape)
	{
		while(block_checkCollision() == 0)
		{
			HAL_Delay(1000);
			time_elapsed++;

			int16_t x1 = 24*x1_pos; int16_t x2 =24*x2_pos;
			int16_t x3 = 24*x3_pos; int16_t x4 =24*x4_pos;
			int16_t y1 = 24*y1_pos; int16_t y2 =24*y2_pos;
			int16_t y3 = 24*y3_pos; int16_t y4 =24*y4_pos;
			spawn_l(x1,y1,LCD_COLOR_BLACK);

			y1 = y1+24; y2 = y2+24; y3 = y3+24; y4 = y4+24;
			spawn_l(x1,y1,LCD_COLOR_CYAN);
			game[y2_pos][x2_pos] = 0;
			game[y2_pos][x2_pos] = 0;
			game[y3_pos][x3_pos] = 0;
			game[y4_pos][x4_pos] = 0;

			game[y1_pos+1][x1_pos] =1;
			game[y2_pos+1][x2_pos] =1;
			game[y3_pos+1][x3_pos] =1;
			game[y4_pos+1][x4_pos] =1;
			y1_pos++; y2_pos++; y3_pos++; y4_pos++;
		}
		block_place();
	}
	else if(block == j_shape)
	{
		while(block_checkCollision() == 0)
		{
			HAL_Delay(1000);
			time_elapsed++;

			int16_t x1 = 24*x1_pos; int16_t x2 =24*x2_pos;
			int16_t x3 = 24*x3_pos; int16_t x4 =24*x4_pos;
			int16_t y1 = 24*y1_pos; int16_t y2 =24*y2_pos;
			int16_t y3 = 24*y3_pos; int16_t y4 =24*y4_pos;
			spawn_j(x1,y1,LCD_COLOR_BLACK);

			y1 = y1+24; y2 = y2+24; y3 = y3+24; y4 = y4+24;
			spawn_j(x1,y1,LCD_COLOR_MAGENTA);
			game[y2_pos][x2_pos] = 0;
			game[y2_pos][x2_pos] = 0;
			game[y3_pos][x3_pos] = 0;
			game[y4_pos][x4_pos] = 0;

			game[y1_pos+1][x1_pos] =1;
			game[y2_pos+1][x2_pos] =1;
			game[y3_pos+1][x3_pos] =1;
			game[y4_pos+1][x4_pos] =1;
			y1_pos++; y2_pos++; y3_pos++; y4_pos++;
		}
		block_place();
	}
	else if(block == t_shape)
	{
		while(block_checkCollision() == 0)
		{
			HAL_Delay(1000);
			time_elapsed++;

			int16_t x1 = 24*x1_pos; int16_t x2 =24*x2_pos;
			int16_t x3 = 24*x3_pos; int16_t x4 =24*x4_pos;
			int16_t y1 = 24*y1_pos; int16_t y2 =24*y2_pos;
			int16_t y3 = 24*y3_pos; int16_t y4 =24*y4_pos;
			spawn_t(x1,y1,LCD_COLOR_BLACK);

			y1 = y1+24; y2 = y2+24; y3 = y3+24; y4 = y4+24;
			spawn_t(x1,y1,LCD_COLOR_BLUE2);
			game[y2_pos][x2_pos] = 0;
			game[y2_pos][x2_pos] = 0;
			game[y3_pos][x3_pos] = 0;
			game[y4_pos][x4_pos] = 0;

			game[y1_pos+1][x1_pos] =1;
			game[y2_pos+1][x2_pos] =1;
			game[y3_pos+1][x3_pos] =1;
			game[y4_pos+1][x4_pos] =1;
			y1_pos++; y2_pos++; y3_pos++; y4_pos++;
		}
		block_place();
	}
}

void block_rotate()
{

}

void game_Run()
{
	while(1)
	{
		spawn_block();
		block_fall();
	}
}
