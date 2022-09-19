
#include "Chip8.h"
#include <memory>
#include <string>
#include <assert.h>
#include <time.h>

 const char Chip8_DefaultMemoryCharSet[] = {

	0xF0, 0x90, 0x90, 0x90, 0xF0,	// 0
	0x20, 0x60, 0x20, 0x20, 0x70,	// 1
	0xF0, 0x10, 0xF0, 0x80, 0xF0,	// 2	
	0xF0, 0x10, 0xF0, 0x10, 0xF0,	// 3
	0x90, 0x90, 0xF0, 0x10, 0x10,	// 4
	0xF0, 0x80, 0xF0, 0x10, 0xF0,	// 5
	0xF0, 0x80, 0xF0, 0x90, 0xF0,	// 6
	0xF0, 0x10, 0x20, 0x40, 0x40,	// 7
	0xF0, 0x90, 0xF0, 0x90, 0xF0,	// 8
	0xF0, 0x90, 0xF0, 0x10, 0xF0,	// 9
	0xF0, 0x90, 0xF0, 0x90, 0x90,	// A
	0xE0, 0x90, 0xE0, 0x90, 0xE0,	// B
	0xF0, 0x80, 0x80, 0x80, 0xF0,	// C
	0xE0, 0x90, 0x90, 0x90, 0xE0,	// D
	0xF0, 0x80, 0xF0, 0x80, 0x80	// F
};

void Chip8_Init(Chip8* chip8)
{
	memset(chip8, 0, sizeof(Chip8));
	memmove(&chip8->c_mem.memory, Chip8_DefaultMemoryCharSet, sizeof(Chip8_DefaultMemoryCharSet));
}

 void Chip8_LoadFile(Chip8* chip8, const Chip8_data* buff, size_t buff_size)
{

	assert(buff_size + CHIP_8_PROGRAM_MEMORY < CHIP_8_MEMORY);

	memcpy(&chip8->c_mem.memory[CHIP_8_PROGRAM_MEMORY], buff, buff_size);
	chip8->c_regs.PC = CHIP_8_PROGRAM_MEMORY;
}


// implementation of instruction set :
//		4-bit = 1 word, 4 word = 1 opcode
//		nnn or addr - A 12 - bit value, the lowest 12 bits of the instruction
//		n or nibble - A 4 - bit value, the lowest 4 bits of the instruction
//		x - A 4 - bit value, the lower 4 bits of the high byte of the instruction
//		y - A 4 - bit value, the upper 4 bits of the low byte of the instruction
//		kk or byte - An 8 - bit value, the lowest 8 bits of the instruction


static void Chip8_SetRandomNumber(Chip8* chip8, unsigned short opcode)
{
	char x = ((opcode >> 8) & 0x000f);
	char kk = (opcode & 0x00ff);

	srand(time(NULL));
	chip8->c_regs.V[x] = (rand() % 255) & kk;
}

static void Chip8_ExeceuteExtended_8000opcode(Chip8* chip8, unsigned short opcode)
{
	unsigned char x = ((opcode >> 8) & 0x000f);
	unsigned char y = ((opcode >> 4) & 0x000f);
	unsigned char deciding_bit = (opcode & 0x000f);

	switch (deciding_bit)
	{
		// 8xy0 LD Vy Vx, loads the of Vy value into Vx
	case 0x00 :
	{
		chip8->c_regs.V[x] = chip8->c_regs.V[y];
	} break;

		// 8xy1 Vx OR Vy, ORs the value of Vx and Vy and stores the result into Vx
	case 0x01:
	{
		chip8->c_regs.V[x] |= chip8->c_regs.V[y];
	} break;

		// 8xy1 Vx OR Vy, ANDs the value of Vx and Vy and stores the result into Vx
	case 0x02:
	{
		chip8->c_regs.V[x] &= chip8->c_regs.V[y];
	} break;
	
		// 8xy3 Vx ^= Vy, XORs the values
	case 0x03:
	{
		chip8->c_regs.V[x] ^= chip8->c_regs.V[y];
	} break;

		// 8xy4 Vx += Vy, set carry VF
	case 0x04:
	{
		Chip8_data result = chip8->c_regs.V[x] + chip8->c_regs.V[y];
		chip8->c_regs.V[0x0f] = false;
		chip8->c_regs.V[0x0F] = (bool)(result > 0xFF);
		chip8->c_regs.V[x] = (Chip8_data)(result);
	} break;

		// 8xy5 Vx -= Vy, set carry VF
	case 0x05:
	{
		chip8->c_regs.V[0x0f] = false;
		chip8->c_regs.V[0x0f] = (bool)(chip8->c_regs.V[x] > chip8->c_regs.V[y]);
		chip8->c_regs.V[x] -= chip8->c_regs.V[y];

	} break;

		// 8xy6 SHR Vx {, Vy}
	case 0x06:
	{
		chip8->c_regs.V[0x0f] = false;
		chip8->c_regs.V[0x0f] = (bool)(chip8->c_regs.V[x] & 0x01);
		chip8->c_regs.V[x] /= 2;
	} break;


		// 8xy7 SUBN Vx Vy, set Vf to 1 if Vy > 
	case 0x07:
	{
		chip8->c_regs.V[0x0f] = false;
		chip8->c_regs.V[0x0f] = (bool)(chip8->c_regs.V[x] < chip8->c_regs.V[y]);
		chip8->c_regs.V[x] = chip8->c_regs.V[y] - chip8->c_regs.V[x];
	} break;

		// 8xyE SHL Vx {, Vy}, set Vf to 1 if MSB(Vx) == 0x01 
	case 0x0E:
	{
		chip8->c_regs.V[0x0f] = (bool)(chip8->c_regs.V[x] & 0x80);
		chip8->c_regs.V[x] *= 2;
	} break;

	default:
		break;
	}
}

static void Chip8_ExecuteExtendedOpcode(Chip8* chip8, unsigned short opcode)
{
	char nnn = opcode & 0x0fff;
	char y = ((opcode >> 4) & 0x000f);
	char x = ((opcode >> 8) & 0x000f);
	char kk = (opcode & 0x00ff);	
	char n = (opcode & 0x000f);

	switch (opcode & 0xf000)
	{
	// 1nnn JP, jumps to address nnn 
	case 0x1000:
		chip8->c_regs.PC = nnn;
		break;

	// 2nnn CALL, calls a subroutine at the specified address
	case 0x2000:
	{
		Chip8_StackPush(&chip8->c_regs, &chip8->c_stack, opcode);
		chip8->c_regs.PC = nnn;
	} break;

	// 3xkk SE V[x], skips next instruction if kk = V[x]
	case 0x3000:
	{
		if (chip8->c_regs.V[x] == kk);
		chip8->c_regs.PC += 2;
	} break;
	
	// 4xkk SNE V[x], skips next instruction if kk != V[x]
	case 0x4000:
	{
		if (chip8->c_regs.V[x] != kk);
			chip8->c_regs.PC += 2;
	} break;

	// 5xy0 SE Vx Vy, skips next instruction if V[x] == V[y] 
	case 0x5000:
	{
		if (chip8->c_regs.V[x] == chip8->c_regs.V[y])
			chip8->c_regs.PC += 2;
	} break;

	// 6xkk LD Vx, puts the value into register 
	case 0x6000:
	{
		chip8->c_regs.V[x] = kk;
	} break;

	// 7xkk ADD Vx kk, adds the value and stores the result into Vx
	case 0x7000:
	{
		chip8->c_regs.V[x] += kk;
	} break;

	case 0x8000:
	{
		Chip8_ExeceuteExtended_8000opcode(chip8, opcode);
	} break;
	
	// 9xy0, skip next instruction if Vx != Vy
	case 0x9000:
	{
		if (chip8->c_regs.V[x] != chip8->c_regs.V[y]) 
			chip8->c_regs.PC += 2;

	} break;
	
	// sets I to value of nnn
	case 0xA000:
	{
		chip8->c_regs.I = nnn;
	} break;

	// JP V0, addr
	case 0xB000:
	{
		chip8->c_regs.PC = nnn + chip8->c_regs.V[0x00];
	} break;

	// sets Vx as random byte AND kk
	case 0xC000:
	{
		Chip8_SetRandomNumber(chip8, opcode);
	} break;	
	
	// Dxyn, n( height of sprite ) draws a sprite on screen 
	case 0xD000:
	{
		const char* sprite = (char*) &chip8->c_mem.memory[chip8->c_regs.I];
		chip8->c_regs.V[0x0f] = Chip8_DrawSpriteToScreen(&chip8->c_screen, chip8->c_regs.V[x], chip8->c_regs.V[y], sprite, n);
	}
	default :
		break;
	}
}

void Chip8_Execute(Chip8* chip8, unsigned short opcode)
{

	switch (opcode)
	{
	// CLS : clears entire screen
	case 0x00E0:
		Chip8_ClearScreen(&chip8->c_screen);
		break;

	// RET : returns from a subroutine 
	case 0x00EE:
		chip8->c_regs.PC = Chip8_StackPop(&chip8->c_regs, &chip8->c_stack);
		break;

	default:
		Chip8_ExecuteExtendedOpcode(chip8, opcode);	
		break;

	}
	return ;
}
