#include "opcodes_8xxx.h"
int op_8xxx_0(opcode_args arg)
{
    verbose_opcode(arg.vm,arg.op, "V%u = V%u", arg.X, arg.Y);
    return 1;
}
int op_8xxx_1(opcode_args arg)
{
    verbose_opcode(arg.vm,arg.op, "V%u |= V%u", arg.X, arg.Y);
    return 1;
}
int op_8xxx_2(opcode_args arg)
{
    verbose_opcode(arg.vm,arg.op, "V%u &= V%u", arg.X, arg.Y);
    return 1;
}
int op_8xxx_3(opcode_args arg)
{
    verbose_opcode(arg.vm,arg.op, "V%u ^= V%u", arg.X, arg.Y);
    return 1;
}
int op_8xxx_4(opcode_args arg)
{
    verbose_opcode(arg.vm,arg.op, "V%u += V%u", arg.X, arg.Y);
    return 1;
}
int op_8xxx_5(opcode_args arg)
{
    verbose_opcode(arg.vm,arg.op, "V%u -= V%u", arg.X, arg.Y);
    return 1;
}
int op_8xxx_6(opcode_args arg)
{
    verbose_opcode(arg.vm,arg.op, "V%u >>= 1", arg.X);
    return 1;
}
int op_8xxx_7(opcode_args arg)
{
    verbose_opcode(arg.vm,arg.op, "V%u = V%u - V%u", arg.X, arg.Y, arg.X);
    return 1;
}
int op_8xxx_E(opcode_args arg)
{
    verbose_opcode(arg.vm,arg.op, "V%u <<= 1", arg.X);
    return 1;
}
