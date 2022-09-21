#ifndef OPCODES_H_
#define OPCODES_H_
#include "vm.h"
#include "opcode_helpers.h"
#include<stdint.h>
#include<stdarg.h>

typedef int (*op_fptr)(chip8_vm *vm, uint16_t op);

int op_NOP(chip8_vm *vm, uint16_t op);
int op_0xxx(chip8_vm *vm, uint16_t op);
int op_1xxx(chip8_vm *vm, uint16_t op);
int op_2xxx(chip8_vm *vm, uint16_t op);
int op_3xxx(chip8_vm *vm, uint16_t op);
int op_4xxx(chip8_vm *vm, uint16_t op);
int op_5xxx(chip8_vm *vm, uint16_t op);
int op_6xxx(chip8_vm *vm, uint16_t op);
int op_7xxx(chip8_vm *vm, uint16_t op);
int op_8xxx(chip8_vm *vm, uint16_t op);
int op_9xxx(chip8_vm *vm, uint16_t op);
int op_axxx(chip8_vm *vm, uint16_t op);
int op_bxxx(chip8_vm *vm, uint16_t op);
int op_cxxx(chip8_vm *vm, uint16_t op);
int op_dxxx(chip8_vm *vm, uint16_t op);
int op_exxx(chip8_vm *vm, uint16_t op);
int op_fxxx(chip8_vm *vm, uint16_t op);

extern op_fptr op_8xxx_table[];
extern op_fptr op_table[]; 
#endif