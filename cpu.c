#include "cpu.h"
#include "opcodes.h"

#include <stdarg.h>
#include <stdio.h>

ExecStatus cpu_execute(chip8_vm *vm, uint16_t op)
{
    if (!vm) return EXEC_FAILURE;
    (*op_table[op&0xF000])(vm, op);
    return EXEC_SUCCESS;
}