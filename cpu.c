#include "cpu.h"

#include <stdarg.h>
#include <stdio.h>

#include "opcode_helpers.h"
#include "opcodes.h"

int cpu_execute(chip8_vm *vm, uint16_t op)
{
    // Executes a single opcode depending on its type
    if (!vm) {
        vm_panic("vm is NULL, check the program", 8);
    }

    // Gets the most significant 4 bits bits from the opcode
    // to determine the function to call.

    // args - is a struct containing necessary abstractions to be used to execute the opcode
    opcode_args args;
    args.X = get_first_identifier(op);
    args.Y = get_second_identifier(op);
    args.N = get_constant_N(op);
    args.NN = get_constant_NN(op);
    args.NNN = get_constant_NNN(op);
    args.vm = vm;
    args.op = op;
    // key is the index of the function pointer to be executed from the table
    uint8_t key_fn = (op & 0xF000) >> 12;

    // Execute the function with its pointer and return its result
    return (*op_table[key_fn])(args);
}