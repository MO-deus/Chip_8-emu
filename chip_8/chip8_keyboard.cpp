
#include "chip8_keyboard.h"
#include <assert.h>

static void KeyboarKeyInBound(int key)
{
	assert(key >= 0 && key < CHIP_8_KEYBOARD_KEYS);
}

int Chip8_KeyboardMap(Chip8_data* Mapped_Keyboard, char key)
{
	for (int i = 0; i < CHIP_8_KEYBOARD_KEYS; i++)
	{
		if (Mapped_Keyboard[i] == key)
		{
			return int(i);
		}
	}
	return int(CHIP8_KEY_NOT_VALID);
}

void Chip8_KeyboardKeyDown(c8_keyboard* keyboard, int key_index)
{	
	KeyboarKeyInBound(key_index);
	keyboard->keyboard[key_index] = CHIP_8_KEY_DOWN;
	return;
}

void Chip8_KeyboardKeyUp(c8_keyboard* keyboard, int key_index) 
{
	keyboard->keyboard[key_index] = CHIP_8_KEY_UP;
	return;
}

bool Chip8_KeyboardKey_Is_Down(c8_keyboard* keyboard, int key_index)
{
	return keyboard->keyboard[key_index];
}

void Chip8_SetMapKeyboard(c8_keyboard* keyboard, const char* map)
{
	keyboard->map_keyboard = map;
	return;
}
