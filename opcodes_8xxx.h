#ifndef OPCODES_8XXX_H_
#define OPCODES_8XXX_H_
#include "vm.h"
#include "opcode_helpers.h"
#include<stdint.h>

int op_8xxx_0(chip8_vm *vm, uint16_t op);
int op_8xxx_1(chip8_vm *vm, uint16_t op);
int op_8xxx_2(chip8_vm *vm, uint16_t op);
int op_8xxx_3(chip8_vm *vm, uint16_t op);
int op_8xxx_4(chip8_vm *vm, uint16_t op);
int op_8xxx_5(chip8_vm *vm, uint16_t op);
int op_8xxx_6(chip8_vm *vm, uint16_t op);
int op_8xxx_7(chip8_vm *vm, uint16_t op);
int op_8xxx_E(chip8_vm *vm, uint16_t op);
#endif