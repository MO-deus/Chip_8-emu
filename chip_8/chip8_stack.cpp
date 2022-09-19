
#include "chip8_stack.h"
#include <assert.h>

static void Check_StackBoundRequest(c8_registers* registers)
{
	assert(registers->SP < CHIP_8_STACK_DEPTH);
}

void Chip8_StackPush(c8_registers* registers, c8_stack* stack, unsigned short value)
{
	registers->SP += 1;
	Check_StackBoundRequest(registers);
	stack->stack[registers->SP] = value;
}

unsigned short Chip8_StackPop(c8_registers* registers, c8_stack* stack)
{
	Check_StackBoundRequest(registers);	
	unsigned short result = stack->stack[registers->SP];
	registers->SP -= 1;
	return result;
}