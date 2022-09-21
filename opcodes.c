#include "opcodes.h"
#include<stdio.h>
int verbose_enabled = 1;

void print_opcode(uint16_t op) { printf("0x%0*x |", HEX_DISPLAY_SIZE, op); }

void verbose_opcode(chip8_vm *vm, uint16_t op, const char *format, ...)
{
    if (!verbose_enabled) return;

    // Displays the location of program counter, the opcode and the custom
    // message
    if (vm) {
        va_list arguments;
        va_start(arguments, format);
        printf("| 0x%0*x | 0x%0*x | ", HEX_DISPLAY_SIZE, vm->PC,
               HEX_DISPLAY_SIZE, op);
        vprintf(format, arguments);
        printf("\n");
        va_end(arguments);
    }
    else {
        vm_panic("Vm is NULL, INTERNAL ERROR at verbose_output", 1);
    }
}

// Functions for getting specific bytes/bits from the op code
// It is assumed that number of bits in a byte is 8.
uint8_t get_first_identifier(uint16_t op)
{
    // Get a 4-bit identifier X from the opcode
    return (op & 0x0F00) >> 8;
}
uint8_t get_second_identifier(uint16_t op)
{
    // Get a 4-bit identifier Y from the opcode
    return (op & 0x00F0) >> 4;
}

uint8_t get_constant_N(uint16_t op)
{
    return (op & 0x000F);
}

uint8_t get_constant_NN(uint16_t op)
{
    return (op & 0x00FF);
}

// These functions return 1 if the opcode execution was successful
// otherwise returns 0.

int op_NOP(chip8_vm *vm, uint16_t op)
{
    verbose_opcode(vm, op, "NOP");
    return 1;
}

int op_0xxx(chip8_vm *vm, uint16_t op)
{
    if(op == 0x0000)
    {
        return op_NOP(vm, op);
    }
    else if(op == 0x00E0)
    {
        verbose_opcode(vm, op, "clear display");
        return 1;
    }
    else if(op == 0x00E0)
    {
        verbose_opcode(vm, op, "return")
        return 1;
    }
}

int op_1xxx(chip8_vm *vm, uint16_t op)
{

}

int op_2xxx(chip8_vm *vm, uint16_t op)
{

}

int op_3xxx(chip8_vm *vm, uint16_t op)
{

}

int op_4xxx(chip8_vm *vm, uint16_t op)
{

}

int op_5xxx(chip8_vm *vm, uint16_t op)
{

}

int op_6xxx(chip8_vm *vm, uint16_t op)
{

}

int op_7xxx(chip8_vm *vm, uint16_t op)
{

}

int op_8xxx(chip8_vm *vm, uint16_t op)
{

}

int op_9xxx(chip8_vm *vm, uint16_t op)
{

}

int op_axxx(chip8_vm *vm, uint16_t op)
{

}

int op_bxxx(chip8_vm *vm, uint16_t op)
{

}

int op_cxxx(chip8_vm *vm, uint16_t op)
{

}

int op_dxxx(chip8_vm *vm, uint16_t op)
{

}

int op_exxx(chip8_vm *vm, uint16_t op)
{

}

int op_fxxx(chip8_vm *vm, uint16_t op)
{

}

op_fptr op_table []= {
    op_0xxx,
    op_1xxx,
    op_2xxx,
    op_3xxx,
    op_4xxx,
    op_5xxx,
    op_6xxx,
    op_7xxx,
    op_8xxx,
    op_9xxx,
    op_axxx,
    op_bxxx,
    op_cxxx,
    op_dxxx,
    op_exxx,
    op_fxxx,
};