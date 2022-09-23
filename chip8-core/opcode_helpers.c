#include "opcode_helpers.h"

#include <stdint.h>
#include <stdio.h>
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
        printf("Changed dll| 0x%0*x | 0x%0*x | ", HEX_DISPLAY_SIZE, vm->PC,
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

uint8_t get_constant_N(uint16_t op) { return (op & 0x000F); }
uint8_t get_constant_NN(uint16_t op) { return (op & 0x00FF); }
uint16_t get_constant_NNN(uint16_t op) { return (op & 0x0FFF); }