#ifndef OPCODE_HELPERS_H_
#define OPCODE_HELPERS_H_
#include<stdarg.h>
#include<stdint.h>
#include "vm.h"

extern int verbose_enabled;

void print_opcode(uint16_t op);
void verbose_opcode(chip8_vm *vm, uint16_t op, const char *format, ...);
uint8_t get_first_identifier(uint16_t op);
uint8_t get_second_identifier(uint16_t op);
uint8_t get_constant_N(uint16_t op);
uint8_t get_constant_NN(uint16_t op);
uint16_t get_constant_NNN(uint16_t op);
#endif