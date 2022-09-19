
#include "chip8_screen.h"
#include <assert.h>
#include <memory>

void ScreenPixelInBound(int x, int y)
{
	assert((x >= 0 && x < CHIP_8_WINDOW_WIDTH) && (y >= 0 && y < CHIP_8_WINDOW_HEIGHT));
}

void Chip8_SetScreen(c8_screen* screen, int x, int y)
{
	ScreenPixelInBound(x, y);
	screen->pixels[y][x] = true;
}	

bool Chip8_IsPixelSet(c8_screen* screen, int x, int y)
{
	ScreenPixelInBound(x, y);
	return screen->pixels[y][x];
}

bool Chip8_DrawSpriteToScreen(c8_screen* screen, int x_coordinate, int y_coordinate, const char* sprite, int sprite_num)
{
	int SpritePixelCollision = 0;

	for (int y_byte = 0; y_byte < sprite_num; y_byte++)
	{
		char temp_byte = sprite[y_byte];

		// x_byte will be iterated upto 8 bits instead of sprite_num 
		for (int x_byte = 0; x_byte < 8; x_byte++)
		{
			if ((temp_byte & (0b10000000 >> x_byte)) == 0)
				continue;

			if (screen->pixels[(y_coordinate + y_byte) % CHIP_8_WINDOW_HEIGHT][(x_byte + x_coordinate) % CHIP_8_WINDOW_WIDTH])
			{
				SpritePixelCollision = true;
			}
			screen->pixels[(y_coordinate + y_byte) % CHIP_8_WINDOW_HEIGHT][(x_byte + x_coordinate) % CHIP_8_WINDOW_WIDTH] ^= true;
		}
	}
	
	return SpritePixelCollision;
}

void Chip8_ClearScreen(c8_screen* screen)
{
	memset(screen->pixels, 0, sizeof(screen->pixels));
	return;
}
