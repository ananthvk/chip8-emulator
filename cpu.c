#include "cpu.h"
#include "opcodes.h"

#include <stdarg.h>
#include <stdio.h>

int cpu_execute(chip8_vm *vm, uint16_t op)
{
    if (!vm) return 0;
    // Gets the most significant 4 bits bits from the opcode
    // to determine the function to call.
    return (*op_table[(op&0xF000) >> 12])(vm, op);
}