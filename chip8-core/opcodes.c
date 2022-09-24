#include "opcodes.h"

#include <stdio.h>
#include <stdlib.h>

#include "opcodes_8xxx.h"

// The opcode function pointer table
// This function pointer array stores the function corresponding to a opcode's
// identification In op_table, the first 4 bits are used to determine the
// function to call. In op_8xxx_table, the last 4 bits are used to determine the
// function to call.
op_fptr op_table[] = {
    op_0xxx, op_1xxx, op_2xxx, op_3xxx, op_4xxx, op_5xxx, op_6xxx, op_7xxx,
    op_8xxx, op_9xxx, op_axxx, op_bxxx, op_cxxx, op_dxxx, op_exxx, op_fxxx,
};

op_fptr op_8xxx_table[] = {
    op_8xxx_0, op_8xxx_1, op_8xxx_2, op_8xxx_3, op_8xxx_4, op_8xxx_5,
    op_8xxx_6, op_8xxx_7, op_NOP,    op_NOP,    op_NOP,    op_NOP,
    op_NOP,    op_NOP,    op_8xxx_E, op_NOP,
};

// These functions return 1 if the opcode execution was successful
// otherwise returns 0.

int op_NOP(opcode_args arg)
{
    verbose_opcode(arg.vm, arg.op, "NOP");
    return 0;
}

int op_0xxx(opcode_args arg)
{
    if (arg.op == 0x0000) {
        return op_NOP(arg);
    }
    else if (arg.op == 0x00E0) {
        verbose_opcode(arg.vm, arg.op, "clear display");
        return 1;
    }
    else if (arg.op == 0x00E0) {
        // The stack pointer points to one element above the last stored address
        verbose_opcode(arg.vm, arg.op, "return");
        if (arg.vm->SP > 0) {
            arg.vm->PC = arg.vm->stack[--(arg.vm->SP)];
            return 1;
        }
        else {
            // The stack is empty
            vm_panic("Invalid return statement", 9);
            return 0;
        }
    }
    else {
        verbose_opcode(arg.vm, arg.op, "call machine code @ 0x%0*x",
                       HEX_DISPLAY_SIZE, arg.NNN);
        return 1;
    }
}

int op_1xxx(opcode_args arg)
{
    verbose_opcode(arg.vm, arg.op, "goto 0x%0*x", HEX_DISPLAY_SIZE, arg.NNN);

    if (arg.NNN == 0 || arg.NNN <= 512) {
        vm_panic("Invalid goto, less than or equal to 512", 9);
    }
    arg.vm->PC = arg.NNN - 2;
    return 1;
}

int op_2xxx(opcode_args arg)
{
    verbose_opcode(arg.vm, arg.op, "call subroutine @ 0x%0*x", HEX_DISPLAY_SIZE,
                   arg.NNN);
    if (arg.vm->SP == VM_STACK_SIZE) {
        vm_panic("Max stack size reached", 9);
    }
    else {
        arg.vm->stack[arg.vm->SP++] = arg.vm->PC;
        // I am subtracting 2 from program counter, since when the next
        // instruction gets executed The instruction at NNN does not get
        // executed The only issue is if unsigned overflow incase NNN = 0 (which
        // should not happen as programs start at location 512)
        if (arg.NNN == 0 || arg.NNN <= 512) {
            vm_panic("Invalid call subroutine instruction, location <= 512", 9);
        }
        arg.vm->PC = arg.NNN - 2;
    }
    return 1;
}

int op_3xxx(opcode_args arg)
{
    verbose_opcode(arg.vm, arg.op, "if (V%u == %u) skip", arg.X, arg.NN);
    if (arg.vm->registers[arg.X] == arg.NN) {
        // Skip executing the next instruction
        arg.vm->PC += 2;
    }
    return 1;
}

int op_4xxx(opcode_args arg)
{
    verbose_opcode(arg.vm, arg.op, "if (V%u != %u) skip", arg.X, arg.NN);
    if (arg.vm->registers[arg.X] != arg.NN) {
        // Skip executing the next instruction
        arg.vm->PC += 2;
    }
    return 1;
}

int op_5xxx(opcode_args arg)
{
    if (get_constant_N(arg.op) == 0) {
        verbose_opcode(arg.vm, arg.op, "if (V%u == V%u) skip", arg.X, arg.Y);
        if (arg.vm->registers[arg.X] == arg.vm->registers[arg.Y]) {
            // Skip executing the next instruction
            arg.vm->PC += 2;
        }
        return 1;
    }
    return 0;
}

int op_6xxx(opcode_args arg)
{
    verbose_opcode(arg.vm, arg.op, "V%u = %u", arg.X, arg.NN);
    arg.vm->registers[arg.X] = arg.NN;
    return 1;
}

int op_7xxx(opcode_args arg)
{
    verbose_opcode(arg.vm, arg.op, "V%u += %u", arg.X, arg.NN);
    arg.vm->registers[arg.X] += arg.NN;
    return 1;
}
int op_8xxx(opcode_args arg)
{
    return (*op_8xxx_table[get_constant_N(arg.op)])(arg);
}

int op_9xxx(opcode_args arg)
{
    if (get_constant_N(arg.op) == 0) {
        verbose_opcode(arg.vm, arg.op, "if (V%u != V%u) skip", arg.X, arg.Y);

        if (arg.vm->registers[arg.X] != arg.vm->registers[arg.Y]) {
            // Skip executing the next instruction
            arg.vm->PC += 2;
        }

        return 1;
    }
    return 0;
}

int op_axxx(opcode_args arg)
{
    verbose_opcode(arg.vm, arg.op, "I = 0x%0*x", HEX_DISPLAY_SIZE, arg.NNN);
    if (arg.NNN == 0 || arg.NNN <= 512) {
        vm_panic("Invalid set I to address, location <= 512", 9);
    }
    arg.vm->I = arg.NNN;
    return 1;
}

int op_bxxx(opcode_args arg)
{
    verbose_opcode(arg.vm, arg.op, "PC = V0 + %u", arg.NNN);

    arg.vm->PC = arg.vm->registers[0] + arg.NNN;
    // TODO: Check if this overflows
    arg.vm->PC -= 2;
    // As after jumping, PC is incremented in main and instruction at PC is
    // omitted
    return 1;
}

int op_cxxx(opcode_args arg)
{
    verbose_opcode(arg.vm, arg.op, "V%u = rand() & %u", arg.X, arg.NN);
    arg.vm->registers[arg.X] = (rand() % 255) & arg.NN;
    return 1;
}

int op_dxxx(opcode_args arg)
{
    verbose_opcode(arg.vm, arg.op, "draw(V%u, V%u, %u) NOT_IMPL", arg.X, arg.Y,
                   arg.N);
    return 1;
}

int op_exxx(opcode_args arg)
{
    if (arg.NN == 0x9E) {
        verbose_opcode(arg.vm, arg.op, "if (key() == V%u) skip NOT_IMPL",
                       arg.X);
        return 1;
    }
    else if (arg.NN == 0xA1) {
        verbose_opcode(arg.vm, arg.op, "if (key() != V%u) skip ", arg.X);
        return 1;
    }
    else {
        return 0;
    }
}

int op_fxxx(opcode_args arg)
{
    switch (arg.NN) {
        case 0x07:
            verbose_opcode(arg.vm, arg.op, "V%u = get_delay() NOT_IMPL", arg.X);
            break;
        case 0x0A:
            verbose_opcode(arg.vm, arg.op, "V%u = get_key() NOT_IMPL", arg.X);
            break;
        case 0x15:
            verbose_opcode(arg.vm, arg.op, "delay_timer(V%u) NOT_IMPL", arg.X);
            break;
        case 0x18:
            verbose_opcode(arg.vm, arg.op, "sound_timer(V%u) NOT_IMPL", arg.X);
            break;
        case 0x1E:
            verbose_opcode(arg.vm, arg.op, "I += V%u", arg.X);
            arg.vm->I += arg.vm->registers[arg.X];
            break;
        case 0x29:
            verbose_opcode(arg.vm, arg.op, "I = sprite_addr[V%u] NOT_IMPL",
                           arg.X);
            uint8_t X = arg.vm->registers[arg.X];
            if(X > 15)
            {
                vm_panic("Invalid I = sprite_address(), Not less than equal 15", 9);
            }
            arg.vm->I = VM_SPRITE_ADDRESS + (X * 5);
            break;
        case 0x33:
            verbose_opcode(arg.vm, arg.op,
                           "store BCD of V%u at I(0x%0*x), I+1, I+2 NOT_IMPL",
                           arg.X, HEX_DISPLAY_SIZE, arg.vm->I);
            break;
        case 0x55:
            verbose_opcode(arg.vm, arg.op,
                           "Store V0 to V%u at address I(0x%0*x) NOT_IMPL",
                           arg.X, HEX_DISPLAY_SIZE, arg.vm->I);
            break;
        case 0x65:
            verbose_opcode(arg.vm, arg.op,
                           "Fill V0 to V%u, from address I(0x%0*x) NOT_IMPL",
                           arg.X, HEX_DISPLAY_SIZE, arg.vm->I);
            break;

        default:
            return 0;
    }
    return 1;
}
