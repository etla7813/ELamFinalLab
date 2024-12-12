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

uint16_t rotation=1;

uint16_t time_elapsed=0;

uint16_t gameEnd = 0;

void DrawBlock(uint16_t x, uint16_t y, uint16_t color)
{
	//input is array coordinates
	//convert to pixel coords
	//draw cube with pixel coordinates
	//add back grid lines
	uint16_t xpos = 24*x; uint16_t ypos = 24*y;
	for(int16_t i = xpos; i < xpos + xgrid; i++)
	{
		LCD_Draw_Vertical_Line(i, ypos, ygrid, color);
	}
	LCD_Draw_Vertical_Line(xpos,ypos,ygrid, LCD_COLOR_WHITE);
	LCD_Draw_Horizontal_Line(xpos,ypos,xgrid, LCD_COLOR_WHITE);
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
	for(uint16_t i = x; i < x + xgrid ; i++)
	{
		LCD_Draw_Vertical_Line(i, y, ygrid*4, color);
	}
	LCD_Draw_Vertical_Line(x,y, ygrid*4, LCD_COLOR_WHITE);
	LCD_Draw_Horizontal_Line(x,y,xgrid, LCD_COLOR_WHITE);
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
    LCD_Draw_Horizontal_Line(x, y + 2 * ygrid, 2*xgrid, LCD_COLOR_WHITE);
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
    for (uint16_t i = y+ygrid; i < y + 2*ygrid; i++) {
        LCD_Draw_Horizontal_Line(x + xgrid, i, xgrid, color); // Vertical middle block
    }
    LCD_Draw_Vertical_Line(x + xgrid, y, ygrid, LCD_COLOR_WHITE);
    LCD_Draw_Horizontal_Line(x + xgrid, y, xgrid, LCD_COLOR_WHITE);
    LCD_Draw_Horizontal_Line(x + xgrid, y + ygrid, xgrid, LCD_COLOR_WHITE);
}

uint16_t block =0;
void spawn_block()
{
	block = RNG_getVal() % 7;
	//block = 6; //testing for rotations
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
		return 1;
	else if(board[y2_pos + 1][x2_pos] == 1 || y2_pos == 10)
		return 1;
	else if(board[y3_pos + 1][x3_pos] == 1 || y3_pos == 10)
		return 1;
	else if(board[y4_pos + 1][x4_pos] == 1 || y4_pos == 10)
		return 1;
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
	rotation = 1;
	check_gameEnd();
}

void block_fall()
{
	//dont ask why i did this i was discovering how extern properly worked lol
	extern uint16_t block;
	extern uint16_t y1_pos; extern uint16_t y2_pos; extern uint16_t y3_pos; extern uint16_t y4_pos;
	extern uint16_t x1_pos; extern uint16_t x2_pos; extern uint16_t x3_pos; extern uint16_t x4_pos;
	if(rotation > 4)
		rotation = 1;
	if(block==square)
	{
		while(block_checkCollision() == 0)
		{
			HAL_Delay(1000);

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
			if(rotation == 1 || rotation == 3)
			{
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
			else if(rotation == 2 || rotation == 4)
			{
				DrawBlock(x1_pos, y1_pos, LCD_COLOR_BLACK);
				DrawBlock(x2_pos, y2_pos, LCD_COLOR_BLACK);
				DrawBlock(x3_pos, y3_pos, LCD_COLOR_BLACK);
				DrawBlock(x4_pos, y4_pos, LCD_COLOR_BLACK);

				DrawBlock(x1_pos, y1_pos +1, LCD_COLOR_BLUE);
				DrawBlock(x2_pos, y2_pos +1, LCD_COLOR_BLUE);
				DrawBlock(x3_pos, y3_pos +1, LCD_COLOR_BLUE);
				DrawBlock(x4_pos, y4_pos +1, LCD_COLOR_BLUE);

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

		}
		block_place();
	}
	else if(block == s_shape)
	{
		while(block_checkCollision() == 0)
		{
			HAL_Delay(1000);
			if(rotation == 1 || rotation == 3)
			{
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
			else if(rotation == 2 || rotation == 4)
			{
				DrawBlock(x1_pos, y1_pos, LCD_COLOR_BLACK);
				DrawBlock(x2_pos, y2_pos, LCD_COLOR_BLACK);
				DrawBlock(x3_pos, y3_pos, LCD_COLOR_BLACK);
				DrawBlock(x4_pos, y4_pos, LCD_COLOR_BLACK);

				DrawBlock(x1_pos, y1_pos +1, LCD_COLOR_RED);
				DrawBlock(x2_pos, y2_pos +1, LCD_COLOR_RED);
				DrawBlock(x3_pos, y3_pos +1, LCD_COLOR_RED);
				DrawBlock(x4_pos, y4_pos +1, LCD_COLOR_RED);

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

		}
		block_place();
	}
	else if(block == z_shape)
	{
		while(block_checkCollision() == 0)
		{
			HAL_Delay(1000);
			if(rotation == 1 || rotation == 3)
			{
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
			else if(rotation == 2 || rotation == 4)
			{
				DrawBlock(x1_pos, y1_pos, LCD_COLOR_BLACK);
				DrawBlock(x2_pos, y2_pos, LCD_COLOR_BLACK);
				DrawBlock(x3_pos, y3_pos, LCD_COLOR_BLACK);
				DrawBlock(x4_pos, y4_pos, LCD_COLOR_BLACK);

				DrawBlock(x1_pos, y1_pos +1, LCD_COLOR_GREEN);
				DrawBlock(x2_pos, y2_pos +1, LCD_COLOR_GREEN);
				DrawBlock(x3_pos, y3_pos +1, LCD_COLOR_GREEN);
				DrawBlock(x4_pos, y4_pos +1, LCD_COLOR_GREEN);

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

		}
		block_place();
	}
	else if(block == l_shape)
	{
		while(block_checkCollision() == 0)
		{
			HAL_Delay(1000);
			if(rotation == 1)
			{
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
			else if(rotation == 2 || rotation == 3 || rotation == 4)
			{
				DrawBlock(x1_pos, y1_pos, LCD_COLOR_BLACK);
				DrawBlock(x2_pos, y2_pos, LCD_COLOR_BLACK);
				DrawBlock(x3_pos, y3_pos, LCD_COLOR_BLACK);
				DrawBlock(x4_pos, y4_pos, LCD_COLOR_BLACK);

				DrawBlock(x1_pos, y1_pos +1, LCD_COLOR_CYAN);
				DrawBlock(x2_pos, y2_pos +1, LCD_COLOR_CYAN);
				DrawBlock(x3_pos, y3_pos +1, LCD_COLOR_CYAN);
				DrawBlock(x4_pos, y4_pos +1, LCD_COLOR_CYAN);

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
		}
		block_place();
	}
	else if(block == j_shape)
	{
		while(block_checkCollision() == 0)
		{
			HAL_Delay(1000);
			if(rotation == 1)
			{
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
			else if(rotation == 2 || rotation == 3 || rotation == 4)
			{
				DrawBlock(x1_pos, y1_pos, LCD_COLOR_BLACK);
				DrawBlock(x2_pos, y2_pos, LCD_COLOR_BLACK);
				DrawBlock(x3_pos, y3_pos, LCD_COLOR_BLACK);
				DrawBlock(x4_pos, y4_pos, LCD_COLOR_BLACK);

				DrawBlock(x1_pos, y1_pos +1, LCD_COLOR_MAGENTA);
				DrawBlock(x2_pos, y2_pos +1, LCD_COLOR_MAGENTA);
				DrawBlock(x3_pos, y3_pos +1, LCD_COLOR_MAGENTA);
				DrawBlock(x4_pos, y4_pos +1, LCD_COLOR_MAGENTA);

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
		}
		block_place();
	}
	else if(block == t_shape)
	{
		while(block_checkCollision() == 0)
		{
			HAL_Delay(1000);
			if(rotation == 1)
			{
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
			else if(rotation == 2 || rotation == 3 || rotation == 4)
			{
				DrawBlock(x1_pos, y1_pos, LCD_COLOR_BLACK);
				DrawBlock(x2_pos, y2_pos, LCD_COLOR_BLACK);
				DrawBlock(x3_pos, y3_pos, LCD_COLOR_BLACK);
				DrawBlock(x4_pos, y4_pos, LCD_COLOR_BLACK);

				DrawBlock(x1_pos, y1_pos +1, LCD_COLOR_BLUE2);
				DrawBlock(x2_pos, y2_pos +1, LCD_COLOR_BLUE2);
				DrawBlock(x3_pos, y3_pos +1, LCD_COLOR_BLUE2);
				DrawBlock(x4_pos, y4_pos +1, LCD_COLOR_BLUE2);

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
		}
		block_place();
	}
}

void block_rotate()
{
	if(block == square) //lmao it cant rotate
	{
		if(rotation > 4)
			rotation = 1;
	}
	else if(block == rect)
	{
		//make sure the rotation value doesnt go outside 360 degrees
		if(rotation > 4)
			rotation = 1;

		if(rotation == 1 || rotation == 3)
		{
			//fix grid coordinates from horiz
			uint16_t nx2 = x2_pos - 1; uint16_t ny2 = y2_pos + 1;
			uint16_t nx3 = x3_pos - 2; uint16_t ny3 = y3_pos + 2;
			uint16_t nx4 = x4_pos - 3; uint16_t ny4 = y4_pos + 3;
			DrawBlock(x1_pos, y1_pos, LCD_COLOR_BLACK);
			DrawBlock(x2_pos, y2_pos, LCD_COLOR_BLACK);
			DrawBlock(x3_pos, y3_pos, LCD_COLOR_BLACK);
			DrawBlock(x4_pos, y4_pos, LCD_COLOR_BLACK);
			spawn_rect(x1_pos*24, y1_pos*24, LCD_COLOR_BLUE);
			game[y2_pos][x2_pos] = 0; game[y3_pos][x3_pos] = 0; game[y4_pos][x4_pos] = 0;
			game[ny2][nx2] = 1; game[ny3][nx3] = 1; game[ny4][nx4] = 1;
			y2_pos = ny2; y3_pos = ny3; y4_pos = ny4;
			x2_pos = nx2; x3_pos = nx3; x4_pos = nx4;
		}
		else if(rotation == 2 || rotation == 4)
		{
			//shift grid bits to the flat position
			//use draw block function to draw new rect
			//set old array positions to 0 and horiz positions to 1
			uint16_t nx2 = x2_pos + 1; uint16_t ny2 = y2_pos - 1;
			uint16_t nx3 = x3_pos + 2; uint16_t ny3 = y3_pos - 2;
			uint16_t nx4 = x4_pos + 3; uint16_t ny4 = y4_pos - 3;

			spawn_rect(x1_pos *24, y1_pos*24, LCD_COLOR_BLACK);
			DrawBlock(x1_pos, y1_pos, LCD_COLOR_BLUE);
			DrawBlock(nx2, ny2, LCD_COLOR_BLUE);
			DrawBlock(nx3, ny3, LCD_COLOR_BLUE);
			DrawBlock(nx4, ny4, LCD_COLOR_BLUE);
			game[y2_pos][x2_pos] = 0; game[y3_pos][x3_pos] = 0; game[y4_pos][x4_pos] = 0;
			game[ny2][nx2] = 1; game[ny3][nx3] = 1; game[ny4][nx4] = 1;
			y2_pos = ny2; y3_pos = ny3; y4_pos = ny4;
			x2_pos = nx2; x3_pos = nx3; x4_pos = nx4;
		}
	}
	else if(block == s_shape)
	{
		if(rotation > 4)
			rotation = 1;

		if(rotation == 1 || rotation == 3)
		{
			uint16_t nx2 = x2_pos + 1; uint16_t ny2 = y2_pos + 1;
			uint16_t nx3 = x3_pos - 1; uint16_t ny3 = y3_pos + 1;
			uint16_t nx4 = x4_pos - 2; uint16_t ny4 = y4_pos;

			DrawBlock(x1_pos, y1_pos, LCD_COLOR_BLACK);
			DrawBlock(x2_pos, y2_pos, LCD_COLOR_BLACK);
			DrawBlock(x3_pos, y3_pos, LCD_COLOR_BLACK);
			DrawBlock(x4_pos, y4_pos, LCD_COLOR_BLACK);
			spawn_s(x1_pos *24, y1_pos*24, LCD_COLOR_RED);

			game[y2_pos][x2_pos] = 0; game[y3_pos][x3_pos] = 0; game[y4_pos][x4_pos] = 0;
			game[ny2][nx2] = 1; game[ny3][nx3] = 1; game[ny4][nx4] = 1;
			y2_pos = ny2; y3_pos = ny3; y4_pos = ny4;
			x2_pos = nx2; x3_pos = nx3; x4_pos = nx4;
		}
		else if(rotation == 2 || rotation ==4)
		{
			uint16_t nx2 = x2_pos - 1; uint16_t ny2 = y2_pos - 1;
			uint16_t nx3 = x3_pos + 1; uint16_t ny3 = y3_pos - 1;
			uint16_t nx4 = x4_pos + 2; uint16_t ny4 = y4_pos;

			spawn_s(x1_pos *24, y1_pos*24, LCD_COLOR_BLACK);
			DrawBlock(x1_pos, y1_pos, LCD_COLOR_RED);
			DrawBlock(nx2, ny2, LCD_COLOR_RED);
			DrawBlock(nx3, ny3, LCD_COLOR_RED);
			DrawBlock(nx4, ny4, LCD_COLOR_RED);
			game[y2_pos][x2_pos] = 0; game[y3_pos][x3_pos] = 0; game[y4_pos][x4_pos] = 0;
			game[ny2][nx2] = 1; game[ny3][nx3] = 1; game[ny4][nx4] = 1;
			y2_pos = ny2; y3_pos = ny3; y4_pos = ny4;
			x2_pos = nx2; x3_pos = nx3; x4_pos = nx4;
		}
	}

	else if(block == z_shape)
	{
		if(rotation > 4)
			rotation = 1;
		if(rotation == 1 || rotation == 3)
		{
			uint16_t nx2 = x2_pos + 1; uint16_t ny2 = y2_pos - 1;
			uint16_t nx3 = x3_pos + 2; uint16_t ny3 = y3_pos;
			uint16_t nx4 = x4_pos + 3; uint16_t ny4 = y4_pos - 1;
			DrawBlock(x1_pos, y1_pos, LCD_COLOR_BLACK);
			DrawBlock(x2_pos, y2_pos, LCD_COLOR_BLACK);
			DrawBlock(x3_pos, y3_pos, LCD_COLOR_BLACK);
			DrawBlock(x4_pos, y4_pos, LCD_COLOR_BLACK);
			spawn_z(x1_pos *24, y1_pos*24, LCD_COLOR_GREEN);

			game[y2_pos][x2_pos] = 0; game[y3_pos][x3_pos] = 0; game[y4_pos][x4_pos] = 0;
			game[ny2][nx2] = 1; game[ny3][nx3] = 1; game[ny4][nx4] = 1;
			y2_pos = ny2; y3_pos = ny3; y4_pos = ny4;
			x2_pos = nx2; x3_pos = nx3; x4_pos = nx4;
		}
		else if(rotation == 2 || rotation == 4)
		{
			uint16_t nx2 = x2_pos - 1; uint16_t ny2 = y2_pos + 1;
			uint16_t nx3 = x3_pos - 2; uint16_t ny3 = y3_pos;
			uint16_t nx4 = x4_pos - 3; uint16_t ny4 = y4_pos + 1;

			spawn_z(x1_pos *24, y1_pos*24, LCD_COLOR_BLACK);
			DrawBlock(x1_pos, y1_pos, LCD_COLOR_GREEN);
			DrawBlock(nx2, ny2, LCD_COLOR_GREEN);
			DrawBlock(nx3, ny3, LCD_COLOR_GREEN);
			DrawBlock(nx4, ny4, LCD_COLOR_GREEN);

			game[y2_pos][x2_pos] = 0; game[y3_pos][x3_pos] = 0; game[y4_pos][x4_pos] = 0;
			game[ny2][nx2] = 1; game[ny3][nx3] = 1; game[ny4][nx4] = 1;
			y2_pos = ny2; y3_pos = ny3; y4_pos = ny4;
			x2_pos = nx2; x3_pos = nx3; x4_pos = nx4;
		}
	}
	else if(block == l_shape)
	{
		if(rotation > 4)
			rotation = 1;
		if(rotation == 1)
		{
			uint16_t nx2 = x2_pos + 1; uint16_t ny2 = y2_pos + 1;
			uint16_t nx3 = x3_pos + 2; uint16_t ny3 = y3_pos + 2;
			uint16_t nx4 = x4_pos + 3; uint16_t ny4 = y4_pos + 1;
			DrawBlock(x1_pos, y1_pos, LCD_COLOR_BLACK);
			DrawBlock(x2_pos, y2_pos, LCD_COLOR_BLACK);
			DrawBlock(x3_pos, y3_pos, LCD_COLOR_BLACK);
			DrawBlock(x4_pos, y4_pos, LCD_COLOR_BLACK);
			spawn_l(x1_pos *24, y1_pos*24, LCD_COLOR_CYAN);

			game[y2_pos][x2_pos] = 0; game[y3_pos][x3_pos] = 0; game[y4_pos][x4_pos] = 0;
			game[ny2][nx2] = 1; game[ny3][nx3] = 1; game[ny4][nx4] = 1;
			y2_pos = ny2; y3_pos = ny3; y4_pos = ny4;
			x2_pos = nx2; x3_pos = nx3; x4_pos = nx4;
		}
		else if(rotation == 2)
		{
			uint16_t nx2 = x2_pos + 1; uint16_t ny2 = y2_pos - 1;
			uint16_t nx3 = x3_pos + 2; uint16_t ny3 = y3_pos - 2;
			uint16_t nx4 = x4_pos + 1; uint16_t ny4 = y4_pos - 3;

			spawn_l(x1_pos *24, y1_pos*24, LCD_COLOR_BLACK);
			DrawBlock(x1_pos, y1_pos, LCD_COLOR_CYAN);
			DrawBlock(nx2, ny2, LCD_COLOR_CYAN);
			DrawBlock(nx3, ny3, LCD_COLOR_CYAN);
			DrawBlock(nx4, ny4, LCD_COLOR_CYAN);

			game[y2_pos][x2_pos] = 0; game[y3_pos][x3_pos] = 0; game[y4_pos][x4_pos] = 0;
			game[ny2][nx2] = 1; game[ny3][nx3] = 1; game[ny4][nx4] = 1;
			y2_pos = ny2; y3_pos = ny3; y4_pos = ny4;
			x2_pos = nx2; x3_pos = nx3; x4_pos = nx4;
		}
		else if(rotation == 3)
		{
			uint16_t nx2 = x2_pos - 1; uint16_t ny2 = y2_pos - 1;
			uint16_t nx3 = x3_pos - 2; uint16_t ny3 = y3_pos - 2;
			uint16_t nx4 = x4_pos - 3; uint16_t ny4 = y4_pos - 1;
			DrawBlock(x1_pos, y1_pos, LCD_COLOR_BLACK);
			DrawBlock(x2_pos, y2_pos, LCD_COLOR_BLACK);
			DrawBlock(x3_pos, y3_pos, LCD_COLOR_BLACK);
			DrawBlock(x4_pos, y4_pos, LCD_COLOR_BLACK);

			DrawBlock(x1_pos, y1_pos, LCD_COLOR_CYAN);
			DrawBlock(nx2, ny2, LCD_COLOR_CYAN);
			DrawBlock(nx3, ny3, LCD_COLOR_CYAN);
			DrawBlock(nx4, ny4, LCD_COLOR_CYAN);

			game[y2_pos][x2_pos] = 0; game[y3_pos][x3_pos] = 0; game[y4_pos][x4_pos] = 0;
			game[ny2][nx2] = 1; game[ny3][nx3] = 1; game[ny4][nx4] = 1;
			y2_pos = ny2; y3_pos = ny3; y4_pos = ny4;
			x2_pos = nx2; x3_pos = nx3; x4_pos = nx4;
		}
		else if(rotation == 4)
		{
			uint16_t nx2 = x2_pos - 1; uint16_t ny2 = y2_pos + 1;
			uint16_t nx3 = x3_pos - 2; uint16_t ny3 = y3_pos + 2;
			uint16_t nx4 = x4_pos - 1; uint16_t ny4 = y4_pos + 3;
			DrawBlock(x1_pos, y1_pos, LCD_COLOR_BLACK);
			DrawBlock(x2_pos, y2_pos, LCD_COLOR_BLACK);
			DrawBlock(x3_pos, y3_pos, LCD_COLOR_BLACK);
			DrawBlock(x4_pos, y4_pos, LCD_COLOR_BLACK);

			DrawBlock(x1_pos, y1_pos, LCD_COLOR_CYAN);
			DrawBlock(nx2, ny2, LCD_COLOR_CYAN);
			DrawBlock(nx3, ny3, LCD_COLOR_CYAN);
			DrawBlock(nx4, ny4, LCD_COLOR_CYAN);

			game[y2_pos][x2_pos] = 0; game[y3_pos][x3_pos] = 0; game[y4_pos][x4_pos] = 0;
			game[ny2][nx2] = 1; game[ny3][nx3] = 1; game[ny4][nx4] = 1;
			y2_pos = ny2; y3_pos = ny3; y4_pos = ny4;
			x2_pos = nx2; x3_pos = nx3; x4_pos = nx4;
		}
	}
	else if(block == j_shape)
	{
		if(rotation > 4)
			rotation = 1;
		if(rotation == 1)
		{
			uint16_t nx2 = x2_pos + 1; uint16_t ny2 = y2_pos + 1;
			uint16_t nx3 = x3_pos + 2; uint16_t ny3 = y3_pos + 2;
			uint16_t nx4 = x4_pos + 1; uint16_t ny4 = y4_pos + 3;
			DrawBlock(x1_pos, y1_pos, LCD_COLOR_BLACK);
			DrawBlock(x2_pos, y2_pos, LCD_COLOR_BLACK);
			DrawBlock(x3_pos, y3_pos, LCD_COLOR_BLACK);
			DrawBlock(x4_pos, y4_pos, LCD_COLOR_BLACK);
			spawn_j(x1_pos *24, y1_pos*24, LCD_COLOR_MAGENTA);

			game[y2_pos][x2_pos] = 0; game[y3_pos][x3_pos] = 0; game[y4_pos][x4_pos] = 0;
			game[ny2][nx2] = 1; game[ny3][nx3] = 1; game[ny4][nx4] = 1;
			y2_pos = ny2; y3_pos = ny3; y4_pos = ny4;
			x2_pos = nx2; x3_pos = nx3; x4_pos = nx4;
		}
		else if(rotation == 2)
		{
			uint16_t nx2 = x2_pos + 1; uint16_t ny2 = y2_pos - 1;
			uint16_t nx3 = x3_pos + 2; uint16_t ny3 = y3_pos - 2;
			uint16_t nx4 = x4_pos + 3; uint16_t ny4 = y4_pos - 1;

			spawn_j(x1_pos *24, y1_pos*24, LCD_COLOR_BLACK);
			DrawBlock(x1_pos, y1_pos, LCD_COLOR_MAGENTA);
			DrawBlock(nx2, ny2, LCD_COLOR_MAGENTA);
			DrawBlock(nx3, ny3, LCD_COLOR_MAGENTA);
			DrawBlock(nx4, ny4, LCD_COLOR_MAGENTA);

			game[y2_pos][x2_pos] = 0; game[y3_pos][x3_pos] = 0; game[y4_pos][x4_pos] = 0;
			game[ny2][nx2] = 1; game[ny3][nx3] = 1; game[ny4][nx4] = 1;
			y2_pos = ny2; y3_pos = ny3; y4_pos = ny4;
			x2_pos = nx2; x3_pos = nx3; x4_pos = nx4;
		}
		else if(rotation == 3)
		{
			uint16_t nx2 = x2_pos - 1; uint16_t ny2 = y2_pos - 1;
			uint16_t nx3 = x3_pos - 2; uint16_t ny3 = y3_pos - 2;
			uint16_t nx4 = x4_pos - 1; uint16_t ny4 = y4_pos - 3;
			DrawBlock(x1_pos, y1_pos, LCD_COLOR_BLACK);
			DrawBlock(x2_pos, y2_pos, LCD_COLOR_BLACK);
			DrawBlock(x3_pos, y3_pos, LCD_COLOR_BLACK);
			DrawBlock(x4_pos, y4_pos, LCD_COLOR_BLACK);

			DrawBlock(x1_pos, y1_pos, LCD_COLOR_MAGENTA);
			DrawBlock(nx2, ny2, LCD_COLOR_MAGENTA);
			DrawBlock(nx3, ny3, LCD_COLOR_MAGENTA);
			DrawBlock(nx4, ny4, LCD_COLOR_MAGENTA);

			game[y2_pos][x2_pos] = 0; game[y3_pos][x3_pos] = 0; game[y4_pos][x4_pos] = 0;
			game[ny2][nx2] = 1; game[ny3][nx3] = 1; game[ny4][nx4] = 1;
			y2_pos = ny2; y3_pos = ny3; y4_pos = ny4;
			x2_pos = nx2; x3_pos = nx3; x4_pos = nx4;
		}
		else if(rotation == 4)
		{
			uint16_t nx2 = x2_pos - 1; uint16_t ny2 = y2_pos + 1;
			uint16_t nx3 = x3_pos - 2; uint16_t ny3 = y3_pos + 2;
			uint16_t nx4 = x4_pos - 3; uint16_t ny4 = y4_pos + 1;
			DrawBlock(x1_pos, y1_pos, LCD_COLOR_BLACK);
			DrawBlock(x2_pos, y2_pos, LCD_COLOR_BLACK);
			DrawBlock(x3_pos, y3_pos, LCD_COLOR_BLACK);
			DrawBlock(x4_pos, y4_pos, LCD_COLOR_BLACK);

			DrawBlock(x1_pos, y1_pos, LCD_COLOR_MAGENTA);
			DrawBlock(nx2, ny2, LCD_COLOR_MAGENTA);
			DrawBlock(nx3, ny3, LCD_COLOR_MAGENTA);
			DrawBlock(nx4, ny4, LCD_COLOR_MAGENTA);

			game[y2_pos][x2_pos] = 0; game[y3_pos][x3_pos] = 0; game[y4_pos][x4_pos] = 0;
			game[ny2][nx2] = 1; game[ny3][nx3] = 1; game[ny4][nx4] = 1;
			y2_pos = ny2; y3_pos = ny3; y4_pos = ny4;
			x2_pos = nx2; x3_pos = nx3; x4_pos = nx4;
		}
	}
	else if(block == t_shape)
	{
		if(rotation > 4)
			rotation = 1;
		if(rotation == 1)
		{
			uint16_t nx2 = x2_pos + 1; uint16_t ny2 = y2_pos - 1;
			uint16_t nx3 = x3_pos + 2; uint16_t ny3 = y3_pos - 2;
			uint16_t nx4 = x4_pos + 2; uint16_t ny4 = y4_pos + 0;
			DrawBlock(x1_pos, y1_pos, LCD_COLOR_BLACK);
			DrawBlock(x2_pos, y2_pos, LCD_COLOR_BLACK);
			DrawBlock(x3_pos, y3_pos, LCD_COLOR_BLACK);
			DrawBlock(x4_pos, y4_pos, LCD_COLOR_BLACK);
			spawn_t(x1_pos *24, y1_pos*24, LCD_COLOR_BLUE2);

			game[y2_pos][x2_pos] = 0; game[y3_pos][x3_pos] = 0; game[y4_pos][x4_pos] = 0;
			game[ny2][nx2] = 1; game[ny3][nx3] = 1; game[ny4][nx4] = 1;
			y2_pos = ny2; y3_pos = ny3; y4_pos = ny4;
			x2_pos = nx2; x3_pos = nx3; x4_pos = nx4;
		}
		else if(rotation == 2)
		{
			uint16_t nx2 = x2_pos - 1; uint16_t ny2 = y2_pos - 1;
			uint16_t nx3 = x3_pos - 2; uint16_t ny3 = y3_pos - 2;
			uint16_t nx4 = x4_pos + 0; uint16_t ny4 = y4_pos - 2;

			spawn_t(x1_pos *24, y1_pos*24, LCD_COLOR_BLACK);
			DrawBlock(x1_pos, y1_pos, LCD_COLOR_BLUE2);
			DrawBlock(nx2, ny2, LCD_COLOR_BLUE2);
			DrawBlock(nx3, ny3, LCD_COLOR_BLUE2);
			DrawBlock(nx4, ny4, LCD_COLOR_BLUE2);

			game[y2_pos][x2_pos] = 0; game[y3_pos][x3_pos] = 0; game[y4_pos][x4_pos] = 0;
			game[ny2][nx2] = 1; game[ny3][nx3] = 1; game[ny4][nx4] = 1;
			y2_pos = ny2; y3_pos = ny3; y4_pos = ny4;
			x2_pos = nx2; x3_pos = nx3; x4_pos = nx4;
		}
		else if(rotation == 3)
		{
			uint16_t nx2 = x2_pos - 1; uint16_t ny2 = y2_pos + 1;
			uint16_t nx3 = x3_pos - 2; uint16_t ny3 = y3_pos + 2;
			uint16_t nx4 = x4_pos - 2; uint16_t ny4 = y4_pos - 0;
			DrawBlock(x1_pos, y1_pos, LCD_COLOR_BLACK);
			DrawBlock(x2_pos, y2_pos, LCD_COLOR_BLACK);
			DrawBlock(x3_pos, y3_pos, LCD_COLOR_BLACK);
			DrawBlock(x4_pos, y4_pos, LCD_COLOR_BLACK);

			DrawBlock(x1_pos, y1_pos, LCD_COLOR_BLUE2);
			DrawBlock(nx2, ny2, LCD_COLOR_BLUE2);
			DrawBlock(nx3, ny3, LCD_COLOR_BLUE2);
			DrawBlock(nx4, ny4, LCD_COLOR_BLUE2);

			game[y2_pos][x2_pos] = 0; game[y3_pos][x3_pos] = 0; game[y4_pos][x4_pos] = 0;
			game[ny2][nx2] = 1; game[ny3][nx3] = 1; game[ny4][nx4] = 1;
			y2_pos = ny2; y3_pos = ny3; y4_pos = ny4;
			x2_pos = nx2; x3_pos = nx3; x4_pos = nx4;
		}
		else if(rotation == 4)
		{
			uint16_t nx2 = x2_pos + 1; uint16_t ny2 = y2_pos + 1;
			uint16_t nx3 = x3_pos + 2; uint16_t ny3 = y3_pos + 2;
			uint16_t nx4 = x4_pos + 0; uint16_t ny4 = y4_pos + 2;
			DrawBlock(x1_pos, y1_pos, LCD_COLOR_BLACK);
			DrawBlock(x2_pos, y2_pos, LCD_COLOR_BLACK);
			DrawBlock(x3_pos, y3_pos, LCD_COLOR_BLACK);
			DrawBlock(x4_pos, y4_pos, LCD_COLOR_BLACK);

			DrawBlock(x1_pos, y1_pos, LCD_COLOR_BLUE2);
			DrawBlock(nx2, ny2, LCD_COLOR_BLUE2);
			DrawBlock(nx3, ny3, LCD_COLOR_BLUE2);
			DrawBlock(nx4, ny4, LCD_COLOR_BLUE2);

			game[y2_pos][x2_pos] = 0; game[y3_pos][x3_pos] = 0; game[y4_pos][x4_pos] = 0;
			game[ny2][nx2] = 1; game[ny3][nx3] = 1; game[ny4][nx4] = 1;
			y2_pos = ny2; y3_pos = ny3; y4_pos = ny4;
			x2_pos = nx2; x3_pos = nx3; x4_pos = nx4;
		}
	}
}

uint16_t check_gameEnd()
{
	//after a block spawns and sets its game status, check if the spot below the game status on the board is 1
	for(int i =0; i < 9; i++)
	{
		if(board[0][i] == 1)
			return 1;
		else return 0;
	}
	return 0;
}

void game_Run()
{
	while(check_gameEnd() == 0)
	{
		spawn_block();
		block_fall();
	}
	game_End();
}

void game_End()
{
	for(int i = 0; i < 240; i++)
	{
		LCD_Draw_Vertical_Line(i, 120, 40, LCD_COLOR_BLACK);
	}

	LCD_DisplayChar(100,140,'G');
	LCD_DisplayChar(115,140,'a');
	LCD_DisplayChar(125,140,'m');
	LCD_DisplayChar(130,140,'e');
	LCD_DisplayChar(140,140,' ');

	LCD_DisplayChar(100,160,' ');
	LCD_DisplayChar(115,160,'O');
	LCD_DisplayChar(125,160,'v');
	LCD_DisplayChar(130,160,'e');
	LCD_DisplayChar(140,160,'r');

	HAL_Delay(3000);

	LCD_Clear(0, LCD_COLOR_BLACK);

	//writing out time elapsed
	char timeElapsed[4];
	itoa(timer_getTime(), timeElapsed, 10);

	LCD_DisplayChar(90, 160, timeElapsed[0]);
	LCD_DisplayChar(110, 160, timeElapsed[1]);
	LCD_DisplayChar(130, 160, timeElapsed[2]);
	LCD_DisplayChar(150, 160, timeElapsed[3]);
}
