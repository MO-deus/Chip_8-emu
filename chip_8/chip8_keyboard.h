
#pragma once

#ifndef CHIP_8_KEYBOARD_H
#define CHIP_8_KEYBOARD_H

#include "chip8_Config.h"
#include "SDL.h"
#include <stdbool.h>

struct chip8_keyboard
{
	bool keyboard[CHIP_8_KEYBOARD_KEYS] = { 0 };
	const char* map_keyboard;

}typedef c8_keyboard;

// maintains a map between virtual and actual keyboard
int Chip8_KeyboardMap(Chip8_data* map, char key);

// function to press down a key in keyboard
void Chip8_KeyboardKeyDown(c8_keyboard* keyboard, int key_index);

// function to release a keys
void Chip8_KeyboardKeyUp(c8_keyboard* keyboard, int key_index);

// function to get the down key
bool Chip8_KeyboardKey_Is_Down(c8_keyboard* keyboard, int key_index);

// 
void Chip8_SetMapKeyboard(c8_keyboard* keyboard, const char* map);

#endif // !CHIP_8_KEYBOARD_H