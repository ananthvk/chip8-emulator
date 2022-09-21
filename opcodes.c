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

int op_NOP(chip8_vm *vm, uint16_t op)
{
    verbose_opcode(vm, op, "NOP");
    return 0;
}

int op_0xxx(chip8_vm *vm, uint16_t op)
{
    if (op == 0x0000) {
        return op_NOP(vm, op);
    }
    else if (op == 0x00E0) {
        verbose_opcode(vm, op, "clear display");
        return 1;
    }
    else if (op == 0x00E0) {
        verbose_opcode(vm, op, "return");
        return 1;
    }
    else {
        verbose_opcode(vm, op, "call machine code @ 0x%0*x", HEX_DISPLAY_SIZE,
                       get_constant_NNN(op));
        return 1;
    }
}

int op_1xxx(chip8_vm *vm, uint16_t op)
{
    verbose_opcode(vm, op, "goto 0x%0*x", HEX_DISPLAY_SIZE,
                   get_constant_NNN(op));
    return 1;
}

int op_2xxx(chip8_vm *vm, uint16_t op)
{
    verbose_opcode(vm, op, "call subroutine @ 0x%0*x", HEX_DISPLAY_SIZE,
                   get_constant_NNN(op));
    return 1;
}

int op_3xxx(chip8_vm *vm, uint16_t op)
{
    uint8_t X = get_first_identifier(op);
    uint8_t NN = get_constant_NN(op);
    verbose_opcode(vm, op, "if (V%u == %u) skip", X, NN);
    return 1;
}

int op_4xxx(chip8_vm *vm, uint16_t op)
{
    uint8_t X = get_first_identifier(op);
    uint8_t NN = get_constant_NN(op);
    verbose_opcode(vm, op, "if (V%u != %u) skip", X, NN);
    return 1;
}

int op_5xxx(chip8_vm *vm, uint16_t op)
{
    uint8_t X = get_first_identifier(op);
    uint8_t Y = get_first_identifier(op);
    if (get_constant_N(op) == 0) {
        verbose_opcode(vm, op, "if (V%u == V%u) skip", X, Y);
        return 1;
    }
    return 0;
}

int op_6xxx(chip8_vm *vm, uint16_t op)
{
    uint8_t X = get_first_identifier(op);
    uint8_t NN = get_constant_NN(op);
    verbose_opcode(vm, op, "V%u = %u", X, NN);
    return 1;
}

int op_7xxx(chip8_vm *vm, uint16_t op)
{
    uint8_t X = get_first_identifier(op);
    uint8_t NN = get_constant_NN(op);
    verbose_opcode(vm, op, "V%u += %u", X, NN);
    return 1;
}
int op_8xxx(chip8_vm *vm, uint16_t op)
{
    return (*op_8xxx_table[get_constant_N(op)])(vm, op);
}

int op_9xxx(chip8_vm *vm, uint16_t op)
{
    uint8_t X = get_first_identifier(op);
    uint8_t Y = get_first_identifier(op);
    if (get_constant_N(op) == 0) {
        verbose_opcode(vm, op, "if (V%u != V%u) skip", X, Y);
        return 1;
    }
    return 0;
}

int op_axxx(chip8_vm *vm, uint16_t op)
{
    uint16_t NNN = get_constant_NNN(op);
    verbose_opcode(vm, op, "I = 0x%0*x", HEX_DISPLAY_SIZE, NNN);
    return 1;
}

int op_bxxx(chip8_vm *vm, uint16_t op)
{
    uint16_t NNN = get_constant_NNN(op);
    verbose_opcode(vm, op, "PC = V0 + %u", NNN);
    return 1;
}

int op_cxxx(chip8_vm *vm, uint16_t op)
{
    uint8_t X = get_first_identifier(op);
    uint8_t NN = get_constant_NN(op);
    verbose_opcode(vm, op, "V%u = rand() & %u", X, NN);
    return 1;
}

int op_dxxx(chip8_vm *vm, uint16_t op)
{
    uint8_t X = get_first_identifier(op);
    uint8_t Y = get_second_identifier(op);
    uint8_t N = get_constant_N(op);
    verbose_opcode(vm, op, "draw(V%u, V%u, %u)", X, Y, N);
    return 1;
}

int op_exxx(chip8_vm *vm, uint16_t op)
{
    uint8_t X = get_first_identifier(op);
    uint8_t NN = get_constant_NN(op);

    if (NN == 0x9E) {
        verbose_opcode(vm, op, "if (key() == V%u) skip", X);
        return 1;
    }
    else if (NN == 0xA1) {
        verbose_opcode(vm, op, "if (key() != V%u) skip", X);
        return 1;
    }
    else {
        return 0;
    }
}

int op_fxxx(chip8_vm *vm, uint16_t op)
{
    uint8_t X = get_first_identifier(op);
    uint8_t NN = get_constant_NN(op);

    switch (NN) {
        case 0x07:
            verbose_opcode(vm, op, "V%u = get_delay()", X);
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