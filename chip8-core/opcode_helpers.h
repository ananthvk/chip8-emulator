#ifndef OPCODE_HELPERS_H_
#define OPCODE_HELPERS_H_
#include <stdarg.h>
#include <stdint.h>

#include "vm.h"

// Flag to set printing of opcodes or not
extern int verbose_enabled;

// Prints a single opcode on the screen
void print_opcode(uint16_t op);

// Prints the program counter, op code and and the formatted message passed to
// this function
void verbose_opcode(chip8_vm *vm, uint16_t op, const char *format, ...);

// Gets the first identifier, i.e X from the op code
uint8_t get_first_identifier(uint16_t op);

// Gets the second identifier, i.e Y from the op code
uint8_t get_second_identifier(uint16_t op);

/* Gets the constant N, or the last 4 bits from the opcode.
Eg: AXYN, this function returns N (in hexadecimal)*/
uint8_t get_constant_N(uint16_t op);

/* Gets the constant NN, or the last 8 bits from the opcode.
Eg: AXNN, this function returns NN (in hexadecimal)*/
uint8_t get_constant_NN(uint16_t op);

/* Gets the constant NNN, or the last 12 bits from the opcode.
Eg: ANNN, this function returns NNN (in hexadecimal)*/
uint16_t get_constant_NNN(uint16_t op);

void set_verbose();
void unset_verbose();

struct opcode_args {
    chip8_vm *vm;
    uint16_t op;
    uint8_t X;
    uint8_t Y;
    uint8_t N;
    uint8_t NN;
    uint16_t NNN;
};

typedef struct opcode_args opcode_args;

#endif