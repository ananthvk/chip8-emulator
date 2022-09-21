#ifndef OPCODES_H_
#define OPCODES_H_
#include "vm.h"
#include "opcode_helpers.h"
#include<stdint.h>
#include<stdarg.h>

typedef int (*op_fptr)(opcode_args arg);

int op_NOP(opcode_args arg);
int op_0xxx(opcode_args arg);
int op_1xxx(opcode_args arg);
int op_2xxx(opcode_args arg);
int op_3xxx(opcode_args arg);
int op_4xxx(opcode_args arg);
int op_5xxx(opcode_args arg);
int op_6xxx(opcode_args arg);
int op_7xxx(opcode_args arg);
int op_8xxx(opcode_args arg);
int op_9xxx(opcode_args arg);
int op_axxx(opcode_args arg);
int op_bxxx(opcode_args arg);
int op_cxxx(opcode_args arg);
int op_dxxx(opcode_args arg);
int op_exxx(opcode_args arg);
int op_fxxx(opcode_args arg);

extern op_fptr op_8xxx_table[];
extern op_fptr op_table[]; 
#endif