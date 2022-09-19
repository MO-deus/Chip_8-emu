
#pragma once


#ifndef CHIP_8_STACK_H
#define CHIP_8_STACK_H

#include "chip8_Config.h"
#include "chip8_registers.h"
#include <stdint.h>

struct Chip8_stack
{
	unsigned short stack[CHIP_8_STACK_DEPTH];

}typedef c8_stack;

// function to push on the stack
void Chip8_StackPush(c8_registers* registers,c8_stack* stack , unsigned short value);

// function to pop from stack
unsigned short Chip8_StackPop(c8_registers* registers, c8_stack* stack);

#endif // !CHIP_8_STACK_H
