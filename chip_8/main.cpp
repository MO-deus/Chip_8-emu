
// Author : Kush Waikar
// Date : 20/6/2022
// project title : Chip_8 Emulator

#pragma warning(disable:4996)

#include "Chip8.h"
#include "SDL.h"
#include <stdio.h>
#include <iostream>

Chip8_data Chip8_MappedKeyboard[CHIP_8_KEYBOARD_KEYS] = {
			SDLK_0, SDLK_1, SDLK_2, SDLK_3,
			SDLK_4, SDLK_5, SDLK_6, SDLK_7,
			SDLK_8, SDLK_9, SDLK_a, SDLK_b,
			SDLK_c, SDLK_d, SDLK_e, SDLK_f
};


int main(int argc, char* argv[])
{

	const char* filename = "roms/INVADERS";

	FILE* file = fopen(filename, "rb");
	if (file == NULL)
	{
		printf("Unable to open file!\n");
		return -1;
	}
	
	fseek(file, 0, SEEK_END);
	long filesize = ftell(file);
	fseek(file, 0, SEEK_SET);	

	Chip8_data* buffer = new Chip8_data[filesize];

	if (!fread(buffer, filesize, 1, file))
	{
		printf("Unable to read from the file into buffer\n");
		return -1; 
	}

	Chip8 Chip8;
	Chip8_Init(&Chip8);
	Chip8_LoadFile(&Chip8, buffer, filesize);

	//Chip8_DrawSpriteToScreen(&Chip8.c_screen, 12, 10, &Chip8.c_mem.memory[0x00], 5);

	/*Chip8.c_screen.pixels[2][3] = 1;
	Chip8_Execute(&Chip8, 0x00E0);
	printf("%i \n\n", Chip8.c_screen.pixels[2][3]);*/

	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Window* Chip_8_window = SDL_CreateWindow (
		EMULATOR_WINDOW_TITLE,								
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		CHIP_8_WINDOW_WIDTH * CHIP_8_WINDOW_SCALE_MULTIPLIER,
		CHIP_8_WINDOW_HEIGHT * CHIP_8_WINDOW_SCALE_MULTIPLIER,
		SDL_WINDOW_SHOWN );

	SDL_Renderer* Chip_8_renderer = NULL;
	Chip_8_renderer = SDL_CreateRenderer(Chip_8_window, -1, SDL_RENDERER_TARGETTEXTURE);

	// main loop (game loop)
	while (WINDOW_RUNNING)
	{
		SDL_Event C8_EventHandler;
		while (SDL_PollEvent(&C8_EventHandler))
		{
			switch (C8_EventHandler.type)
			{
			case SDL_QUIT:
				goto QUIT_GAME_LOOP;
				break;

			case SDL_KEYDOWN:
			{
				// returns which key is pressed
				uint16_t key = C8_EventHandler.key.keysym.sym;

				// checks if the key presses is valid or not
				int virtual_key = Chip8_KeyboardMap(Chip8_MappedKeyboard, key);
				if (virtual_key != CHIP8_KEY_NOT_VALID)
				{
					Chip8_KeyboardKeyDown(&Chip8.c_keyboard, virtual_key);
				}
			}
				break;

			case SDL_KEYUP:
			{
				// returns which key is pressed
				uint16_t key = C8_EventHandler.key.keysym.sym;

				// checks if the key presses is valid or not
				int virtual_key = Chip8_KeyboardMap(Chip8_MappedKeyboard, key);
				if (virtual_key != CHIP8_KEY_NOT_VALID)
				{
					Chip8_KeyboardKeyUp(&Chip8.c_keyboard, virtual_key);
				}
			}
				break;

			default: break;
			};

			SDL_SetRenderDrawColor(Chip_8_renderer, 255, 255, 255, 255);
			SDL_RenderClear(Chip_8_renderer);
			SDL_SetRenderDrawColor(Chip_8_renderer, 0, 0, 0, 255);

			for (int x = 0; x < CHIP_8_WINDOW_WIDTH; x++)
			{
				for (int y = 0; y < CHIP_8_WINDOW_HEIGHT; y++)
				if(Chip8_IsPixelSet(&Chip8.c_screen,x,y))
				{
					SDL_Rect rect_pixel;
					rect_pixel.x = x * CHIP_8_WINDOW_SCALE_MULTIPLIER;
					rect_pixel.y = y * CHIP_8_WINDOW_SCALE_MULTIPLIER;
					rect_pixel.w = CHIP_8_WINDOW_SCALE_MULTIPLIER;
					rect_pixel.h = CHIP_8_WINDOW_SCALE_MULTIPLIER;
					SDL_RenderFillRect(Chip_8_renderer, &rect_pixel);
				}
			}
			
		SDL_RenderPresent(Chip_8_renderer);

		// delay timer implementation
		if (Chip8.c_regs.delay_timer > 0)
		{
			Sleep(100);
			printf("Delay... \n");
			Chip8.c_regs.delay_timer -= 1;
		}
		
		// sound timer implementation
		if (Chip8.c_regs.sound_timer > 0)
		{
			printf("beep...\n");
			Beep(15000, 100);
			Chip8.c_regs.sound_timer -= 1;
		}

		Chip8_data opcode = Chip8_GetMemoryByte(&Chip8.c_mem, Chip8.c_regs.PC);
		printf("%i \n", opcode);
		Chip8.c_regs.PC += 2;
		Chip8_Execute(&Chip8, opcode); 
		}

	}

QUIT_GAME_LOOP : 
	SDL_DestroyRenderer(Chip_8_renderer);
	SDL_DestroyWindow(Chip_8_window);
	SDL_Quit();

	return 0;
}