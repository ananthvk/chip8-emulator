#include "opcodes_8xxx.h"
int op_8xxx_0(chip8_vm *vm, uint16_t op)
{
    uint8_t X = get_first_identifier(op);
    uint8_t Y = get_first_identifier(op);
    verbose_opcode(vm, op, "V%u = V%u", X, Y);
    return 1;
}
int op_8xxx_1(chip8_vm *vm, uint16_t op)
{
    uint8_t X = get_first_identifier(op);
    uint8_t Y = get_first_identifier(op);
    verbose_opcode(vm, op, "V%u |= V%u", X, Y);
    return 1;
}
int op_8xxx_2(chip8_vm *vm, uint16_t op)
{
    uint8_t X = get_first_identifier(op);
    uint8_t Y = get_first_identifier(op);
    verbose_opcode(vm, op, "V%u &= V%u", X, Y);
    return 1;
}
int op_8xxx_3(chip8_vm *vm, uint16_t op)
{
    uint8_t X = get_first_identifier(op);
    uint8_t Y = get_first_identifier(op);
    verbose_opcode(vm, op, "V%u ^= V%u", X, Y);
    return 1;
}
int op_8xxx_4(chip8_vm *vm, uint16_t op)
{
    uint8_t X = get_first_identifier(op);
    uint8_t Y = get_first_identifier(op);
    verbose_opcode(vm, op, "V%u += V%u", X, Y);
    return 1;
}
int op_8xxx_5(chip8_vm *vm, uint16_t op)
{
    uint8_t X = get_first_identifier(op);
    uint8_t Y = get_first_identifier(op);
    verbose_opcode(vm, op, "V%u -= V%u", X, Y);
    return 1;
}
int op_8xxx_6(chip8_vm *vm, uint16_t op)
{
    uint8_t X = get_first_identifier(op);
    verbose_opcode(vm, op, "V%u >>= 1", X);
    return 1;
}
int op_8xxx_7(chip8_vm *vm, uint16_t op)
{
    uint8_t X = get_first_identifier(op);
    uint8_t Y = get_first_identifier(op);
    verbose_opcode(vm, op, "V%u = V%u - V%u", X, Y, X);
    return 1;
}
int op_8xxx_E(chip8_vm *vm, uint16_t op)
{
    uint8_t X = get_first_identifier(op);
    verbose_opcode(vm, op, "V%u <<= 1", X);
    return 1;
}
