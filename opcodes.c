#include "opcodes.h"

#include <stdio.h>

#include "opcodes_8xxx.h"

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
        verbose_opcode(arg.vm, arg.op, "return");
        return 1;
    }
    else {
        verbose_opcode(arg.vm, arg.op, "call machine code @ 0x%0*x",
                       HEX_DISPLAY_SIZE, get_constant_NNN(arg.op));
        return 1;
    }
}

int op_1xxx(opcode_args arg)
{
    verbose_opcode(arg.vm, arg.op, "goto 0x%0*x", HEX_DISPLAY_SIZE,
                   get_constant_NNN(arg.op));
    return 1;
}

int op_2xxx(opcode_args arg)
{
    verbose_opcode(arg.vm, arg.op, "call subroutine @ 0x%0*x", HEX_DISPLAY_SIZE,
                   get_constant_NNN(arg.op));
    return 1;
}

int op_3xxx(opcode_args arg)
{
    verbose_opcode(arg.vm, arg.op, "if (V%u == %u) skip", arg.X, arg.NN);
    return 1;
}

int op_4xxx(opcode_args arg)
{
    verbose_opcode(arg.vm, arg.op, "if (V%u != %u) skip", arg.X, arg.NN);
    return 1;
}

int op_5xxx(opcode_args arg)
{
    if (get_constant_N(arg.op) == 0) {
        verbose_opcode(arg.vm, arg.op, "if (V%u == V%u) skip", arg.X, arg.Y);
        return 1;
    }
    return 0;
}

int op_6xxx(opcode_args arg)
{
    verbose_opcode(arg.vm, arg.op, "V%u = %u", arg.X, arg.NN);
    return 1;
}

int op_7xxx(opcode_args arg)
{
    verbose_opcode(arg.vm, arg.op, "V%u += %u", arg.X, arg.NN);
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
        return 1;
    }
    return 0;
}

int op_axxx(opcode_args arg)
{
    verbose_opcode(arg.vm, arg.op, "I = 0x%0*x", HEX_DISPLAY_SIZE, arg.NNN);
    return 1;
}

int op_bxxx(opcode_args arg)
{
    verbose_opcode(arg.vm, arg.op, "PC = V0 + %u", arg.NNN);
    return 1;
}

int op_cxxx(opcode_args arg)
{
    verbose_opcode(arg.vm, arg.op, "V%u = rand() & %u", arg.X, arg.NN);
    return 1;
}

int op_dxxx(opcode_args arg)
{
    verbose_opcode(arg.vm, arg.op, "draw(V%u, V%u, %u)", arg.X, arg.Y, arg.N);
    return 1;
}

int op_exxx(opcode_args arg)
{
    if (arg.NN == 0x9E) {
        verbose_opcode(arg.vm, arg.op, "if (key() == V%u) skip", arg.X);
        return 1;
    }
    else if (arg.NN == 0xA1) {
        verbose_opcode(arg.vm, arg.op, "if (key() != V%u) skip", arg.X);
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
            verbose_opcode(arg.vm, arg.op, "V%u = get_delay()", arg.X);
            break;
        case 0x0A:
            break;
        case 0x15:
            break;
        case 0x18:
            break;
        case 0x1E:
            break;
        case 0x29:
            break;
        case 0x33:
            break;
        case 0x55:
            break;
        case 0x65:
            break;

        default:
            return 0;
    }
    return 1;
}
