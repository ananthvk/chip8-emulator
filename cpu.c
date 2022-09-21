#include "cpu.h"
#include "opcodes.h"
#include "opcode_helpers.h"

#include <stdarg.h>
#include <stdio.h>

int cpu_execute(chip8_vm *vm, uint16_t op)
{
    if (!vm) return 0;
    // Gets the most significant 4 bits bits from the opcode
    // to determine the function to call.
    uint8_t X = get_first_identifier(op);
    uint8_t Y = get_second_identifier(op);
    uint8_t N = get_constant_N(op);
    uint8_t NN = get_constant_NN(op);
    uint16_t NNN = get_constant_NNN(op);
    uint8_t key_fn = (op&0xF000) >> 12;
    return (*op_table[key_fn])(vm, op);
}