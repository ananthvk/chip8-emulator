#include "cpu.h"

#include <stdarg.h>
#include <stdio.h>

#include "opcode_helpers.h"
#include "opcodes.h"

int cpu_execute(chip8_vm *vm, uint16_t op)
{
    if (!vm) return 0;
    // Gets the most significant 4 bits bits from the opcode
    // to determine the function to call.
    opcode_args args;
    args.X = get_first_identifier(op);
    args.Y = get_second_identifier(op);
    args.N = get_constant_N(op);
    args.NN = get_constant_NN(op);
    args.NNN = get_constant_NNN(op);
    args.vm = vm;
    uint8_t key_fn = (op & 0xF000) >> 12;

    return (*op_table[key_fn])(args);
}