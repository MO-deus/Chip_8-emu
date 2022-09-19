
#include "chip8_mem.h"
#include <assert.h>

// function to check if the memory write request is in bound
static void Chip8_CheckMemRequest(int index)
{
	assert(index >= 0 && index < CHIP_8_MEMORY);
}

void Chip8_SetMemory(c8_mem* C8_memory, unsigned int index, unsigned char value)
{
	Chip8_CheckMemRequest(index);
	C8_memory->memory[index] = value;
}


Chip8_data Chip8_GetMemory(c8_mem* C8_memory, unsigned int index)
{
	Chip8_CheckMemRequest(index);
	return C8_memory->memory[index];
}

Chip8_data Chip8_GetMemoryByte(c8_mem* memory, int index)
{
	Chip8_CheckMemRequest(index);
	Chip8_data byte_1 = Chip8_GetMemory(memory, index);
	Chip8_data byte_2 = Chip8_GetMemory(memory, index + 1);

	return ((byte_1 << 8) | byte_2);
}
