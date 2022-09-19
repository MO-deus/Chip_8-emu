
#pragma once

#ifndef CHIP_8_SCRREN_H
#define CHIP_8_SCRREN_H

#include "chip8_Config.h"
#include <stdint.h>
#include <stdbool.h>

struct Chip8_screen
{
	bool pixels[CHIP_8_WINDOW_HEIGHT][CHIP_8_WINDOW_WIDTH] ;

}typedef c8_screen;

// sets the corresponding pixel defined by the co-ordinates
void Chip8_SetScreen(c8_screen* screen, int y, int x);

// returns value of pixel as set/unset
bool Chip8_IsPixelSet(c8_screen* screen, int x, int y);

// function to draw a sprite on screen
// sprites are drawn by XORing the pixel with sprite byte
bool Chip8_DrawSpriteToScreen(c8_screen* screen, int x_coordinate, int y_coordinate, const char* spirte, int sprite_num);

// function to clear the screen 
void Chip8_ClearScreen(c8_screen* screen);

#endif // !CHIP_8_SCRREN_H
 