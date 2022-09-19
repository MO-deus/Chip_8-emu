
#pragma once

#ifndef CHIP_8_REGISTERS
#define CHIP_8_REGISTERS
#include <stdint.h>
#include "chip8_Config.h"

struct Chip8_registers
{
	// Chip has 16 general purpose registers 
	// naming : V0,V1,V2.......VF 
	// VF is used as flag register
	Chip8_data V[CHIP_8_TOTAL_REGISTERS] = { 0 };

	// a 16 bit register [ I ] for addresses
	Chip8_data I = NULL;

	// timers
	Chip8_data delay_timer = 0;
	Chip8_data sound_timer = 0 ;

	// special purpose registers
	Chip8_data PC = NULL;
	Chip8_data SP = NULL;

}typedef c8_registers;


#endif // !CHIP_8_REGISTERS

