
#pragma once

#include <stdint.h>

#ifndef CONFIG_H
#define CONFIG_H

#define EMULATOR_WINDOW_TITLE "Chip 8 Emu ~ UwU ~"

// 4kb memory
#define CHIP_8_MEMORY 4096 // in bytes

// 64 x 32 display
#define CHIP_8_WINDOW_WIDTH 64
#define CHIP_8_WINDOW_HEIGHT 32

// window scale 
#define CHIP_8_WINDOW_SCALE_MULTIPLIER 10 

// total number of registers
#define CHIP_8_TOTAL_REGISTERS 16	

// stack depth : 16
#define CHIP_8_STACK_DEPTH 16

// total number keyboard keys
#define CHIP_8_KEYBOARD_KEYS 16

// key down means true
// key up means false
#define CHIP_8_KEY_DOWN 1
#define CHIP_8_KEY_UP 0

// when an undefined key is pressed, an error value will be generated
// usage : Chip8_KeyboardMap() function
#define CHIP8_KEY_NOT_VALID -1

// starting memory of chip 8 programmable memory
#define	CHIP_8_PROGRAM_MEMORY 0x200

typedef char Chip8_data;
#endif // !CONFIG_H
