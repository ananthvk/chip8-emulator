#include "opcodes_8xxx.h"
int op_8xxx_0(opcode_args arg)
{
    verbose_opcode(arg.vm, arg.op, "V%u = V%u", arg.X, arg.Y);
    arg.vm->registers[arg.X] = arg.vm->registers[arg.Y];
    return 1;
}
int op_8xxx_1(opcode_args arg)
{
    verbose_opcode(arg.vm, arg.op, "V%u |= V%u", arg.X, arg.Y);
    arg.vm->registers[arg.X] |= arg.vm->registers[arg.Y];
    return 1;
}
int op_8xxx_2(opcode_args arg)
{
    verbose_opcode(arg.vm, arg.op, "V%u &= V%u", arg.X, arg.Y);
    arg.vm->registers[arg.X] &= arg.vm->registers[arg.Y];
    return 1;
}
int op_8xxx_3(opcode_args arg)
{
    verbose_opcode(arg.vm, arg.op, "V%u ^= V%u", arg.X, arg.Y);
    arg.vm->registers[arg.X] ^= arg.vm->registers[arg.Y];
    return 1;
}
int op_8xxx_4(opcode_args arg)
{
    verbose_opcode(arg.vm, arg.op, "V%u += V%u", arg.X, arg.Y);
    uint8_t X = arg.vm->registers[arg.X];
    uint8_t Y = arg.vm->registers[arg.Y];
    // TODO: Check that these carry / VF / overflow functions are correct
    if (((int)X + (int)Y) > 255) {
        // Check if a overflow occurs
        arg.vm->registers[0xF] = 1;
    }
    else {
        // No overflow has occured
        arg.vm->registers[0xF] = 0;
    }
    arg.vm->registers[arg.X] += arg.vm->registers[arg.Y];
    return 1;
}
int op_8xxx_5(opcode_args arg)
{
    verbose_opcode(arg.vm, arg.op, "V%u -= V%u", arg.X, arg.Y);
    uint8_t X = arg.vm->registers[arg.X];
    uint8_t Y = arg.vm->registers[arg.Y];
    if (X < Y) {
        // Overflow will occur when performing Vx - Vy
        arg.vm->registers[0xF] = 1;
    }
    else {
        arg.vm->registers[0xF] = 0;
    }
    arg.vm->registers[arg.X] -= arg.vm->registers[arg.Y];
    return 1;
}
int op_8xxx_6(opcode_args arg)
{
    verbose_opcode(arg.vm, arg.op, "V%u >>= 1", arg.X);
    // Stores least significant byte in Vf and then right shifts by 1
    arg.vm->registers[0xF] = get_constant_N(arg.op);
    arg.vm->registers[arg.X] >>= 1;
    return 1;
}
int op_8xxx_7(opcode_args arg)
{
    verbose_opcode(arg.vm, arg.op, "V%u = V%u - V%u", arg.X, arg.Y, arg.X);
    uint8_t X = arg.vm->registers[arg.X];
    uint8_t Y = arg.vm->registers[arg.Y];
    if (X > Y) {
        // Overflow will occur when performing Vx - Vy
        arg.vm->registers[0xF] = 1;
    }
    else {
        arg.vm->registers[0xF] = 0;
    }
    arg.vm->registers[arg.X] =
        arg.vm->registers[arg.Y] - arg.vm->registers[arg.X];
    return 1;
}
int op_8xxx_E(opcode_args arg)
{
    verbose_opcode(arg.vm, arg.op, "V%u <<= 1", arg.X);
    // Stores the most significant bit in Vf
    arg.vm->registers[0xF] = (arg.vm->registers[arg.X] & 0xff) >> 7;
    arg.vm->registers[arg.X] <<= 1;
    return 1;
}
