#ifndef SYSTEM_H
#define SYSTEM_H

#include <stdio.h>

#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>

#ifdef _WIN32
#define GLEW_STATIC
#include <GL/glew.h>
#undef main
#endif

#define SYSTEM_WIDTH 1024
#define SYSTEM_HEIGHT 768
#define SYSTEM_TITLE "Virtual Machine"

// System definitions:

#define RAM_SIZE 65536

// Registers:
/* general 8 bit registers (breakdown of 16 bit registers) */
#define AL 11 // CONTINUES FROM FLG
#define AH 12
#define BL 13
#define BH 14
#define CL 15
#define CH 16
#define DL 17
#define DH 18
/* general 16 bit registers */
#define AX 19
#define BX 20
#define CX 21
#define DX 22
/* general 32 bit registers */
#define TMP 0 // FOR SYSTEM USE ONLY
#define EAX 1 // accumulator
#define EBX 2 // other
#define ECX 3 // other
#define EDX 4 // program counter
/* special registers - these are all full 32 bit integers since they are indices */
#define ESB 5  // stack base pointer; points to the bottom of the stack
#define ESP 6  // stack pointer; points to the top of the stack
#define ESI 7  // stack source index
#define EDI 8  // stack destination index
#define EIP 9  // program counter; read only register
#define FLG 10 // flag register
#define REGISTER_COUNT 11

// Flags:
#define EQ_FLAG 1 // EQUAL FLAG
#define GT_FLAG 2 // GREATER FLAG
#define LS_FLAG 4 // LESS FLAG

// BIOS:
#define BIOS_EXIT       1
#define BIOS_PRINT_INT  2
#define BIOS_PRINT_CHAR 3
#define BIOS_READ_DISK  4
#define BIOS_WRITE_DISK 5

// Opcodes:
// Designed to be minimalistic
#define NONE   0
#define MOV    1  // 2 registers
#define MOVB   2  // 1 register, 1 byte
#define MOVS   3  // 1 register, 1 short
#define MOVI   4  // 1 register, 1 int
#define MOVF   5  // 1 register, 1 float
#define INT    6  // byte
#define CMP    7  // 2 registers
#define ADD    8  // 3 registers
#define SUB    9  // 3 registers
#define MUL   10  // 3 registers
#define DIV   11  // 3 registers
#define JMP   12  // 2 registers
#define JEQ   13  // 2 registers
#define JNE   14  // 2 registers 
#define JGE   15  // 2 registers
#define JLE   16  // 2 registers
#define POP   17  // 1 register
#define PUSH  18  // 1 register 
#define FETCH 19  // 1 register
#define WRITE 20  // 1 register

namespace System
{
	int execute(const char* file);
}

#endif /* SYSTEM_H */