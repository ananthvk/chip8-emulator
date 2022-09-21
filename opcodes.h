#ifndef OPCODES_H_
#define OPCODES_H_
#include "vm.h"
#include<stdint.h>
#include<stdarg.h>

#define HEX_DISPLAY_SIZE 4
typedef int (*op_fptr)(chip8_vm *vm, uint16_t op);

extern op_fptr op_table[]; 
#endif