/*
 * Block_Driver.c
 *
 *  Created on: Dec 7, 2024
 *      Author: Ethan
 */


#include <Block_Driver.h>


void grid_Init()
{
	int board[8][10] = {
			{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
			{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
			{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
			{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
			{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
			{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
			{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
			{0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
	};

	int game[8][10] = {
		    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
		};
}

void blockFall()
{

}

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
	for(uint16_t i = x; i < x + xgrid*4 ; i++)
	{
		LCD_Draw_Vertical_Line(i, y, ygrid, color);
	}
	LCD_Draw_Vertical_Line(x,y,ygrid, LCD_COLOR_WHITE);
	LCD_Draw_Horizontal_Line(x,y,xgrid, LCD_COLOR_WHITE);

	LCD_Draw_Vertical_Line(x+xgrid,y,ygrid, LCD_COLOR_WHITE);
	LCD_Draw_Horizontal_Line(x+xgrid,y,xgrid, LCD_COLOR_WHITE);

	LCD_Draw_Vertical_Line(x+2*xgrid,y,ygrid, LCD_COLOR_WHITE);
	LCD_Draw_Horizontal_Line(x+2*xgrid,y,xgrid, LCD_COLOR_WHITE);

	LCD_Draw_Vertical_Line(x+3*xgrid,y,ygrid, LCD_COLOR_WHITE);
	LCD_Draw_Horizontal_Line(x+3*xgrid,y,xgrid, LCD_COLOR_WHITE);
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
    for (uint16_t i = y; i < y + 2 * ygrid; i++) {
        LCD_Draw_Horizontal_Line(x, i, xgrid, color); // Vertical part of the "L"
    }
    LCD_Draw_Vertical_Line(x, y, ygrid, LCD_COLOR_WHITE);
    LCD_Draw_Vertical_Line(x, y + ygrid, ygrid, LCD_COLOR_WHITE);
    LCD_Draw_Horizontal_Line(x, y, xgrid, LCD_COLOR_WHITE);
    LCD_Draw_Horizontal_Line(x, y + ygrid, xgrid, LCD_COLOR_WHITE);

    // Block 3 (Bottom horizontal line)
    for (uint16_t i = x; i < x + xgrid; i++) {
        LCD_Draw_Vertical_Line(i, y + 2 * ygrid, ygrid, color); // Bottom part of the "L"
    }
    LCD_Draw_Vertical_Line(x, y + 2 * ygrid, ygrid, LCD_COLOR_WHITE);
    LCD_Draw_Horizontal_Line(x, y + 2 * ygrid, xgrid, LCD_COLOR_WHITE);
    LCD_Draw_Horizontal_Line(x + xgrid, y + 2 * ygrid, xgrid, LCD_COLOR_WHITE);
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


void spawn_block()
{
	uint16_t block = RNG_getVal() % 7;
	if(block == square)
	{
		spawn_square(xstart2, 0, LCD_COLOR_YELLOW);
	}
	else if (block == rect)
	{
		spawn_rect(xstart2, 0, LCD_COLOR_BLUE);
	}
	else if (block == s_shape)
	{
		spawn_s(xstart2, 0, LCD_COLOR_RED);
	}
	else if (block == z_shape)
	{
		spawn_z(xstart2, 0, LCD_COLOR_GREEN);
	}
	else if (block == l_shape)
	{
		spawn_l(xstart2, 0, LCD_COLOR_CYAN);
	}
	else if (block == j_shape)
	{
		spawn_j(xstart2, 0, LCD_COLOR_MAGENTA);
	}
	else if (block == t_shape)
	{
		spawn_t(xstart2, 0, LCD_COLOR_BLUE2);
	}
	else
	{
		spawn_l(xstart2, 0, LCD_COLOR_CYAN);
	}
}
