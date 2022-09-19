#pragma once

#ifndef CHIP_8_H
#define CHIP_8_H



#define WINDOW_RUNNING 1

#include "chip8_Config.h"
#include "chip8_mem.h"
#include "chip8_registers.h"
#include "chip8_stack.h"
#include "chip8_keyboard.h"
#include "chip8_screen.h"
#include <Windows.h>

struct Chip8
{
	c8_mem c_mem;
	c8_registers c_regs;
	c8_stack c_stack;
	c8_keyboard c_keyboard;
	c8_screen c_screen;

}typedef Chip8;

// initializes memory to a chip8 instance
void Chip8_Init(Chip8* chip8);

// loads opcode file into memory
void Chip8_LoadFile(Chip8* chip8, const Chip8_data* buff, size_t buff_size);

// executes the opcode from loaded file
void Chip8_Execute(Chip8* chip8, unsigned short opcode);

#endif // !CHIP_8_H
