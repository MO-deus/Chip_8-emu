
#pragma once

#ifndef CHIP_8_MEMORY_H
#define CHIP_8_MEMORY_H

#include "chip8_Config.h"
#include<stdint.h>

struct chip8_memory 
{
	char memory[CHIP_8_MEMORY];	// RAM

}typedef c8_mem;


// function to set chip8 memory
void Chip8_SetMemory(c8_mem* C8_memory, unsigned int index, const Chip8_data value);

// function to get from memory
Chip8_data Chip8_GetMemory(c8_mem* C8_memory, unsigned int index);

// function to get 2 bytes from memory
Chip8_data Chip8_GetMemoryByte(c8_mem* memory, int index);


#endif // !CHIP_8_MEMORY_H
