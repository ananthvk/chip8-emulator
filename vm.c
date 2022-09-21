#include "vm.h"
#include <stdio.h>
#include<string.h>
#include <stdlib.h>
void vm_init(chip8_vm *vm)
{
    vm->PC = VM_START_ADDRESS;
    vm->SP = 0;
    vm->I = 0;
    vm->timer_delay = 0;
    vm->timer_sound = 0;
    memset(vm->registers, 0, sizeof(vm->registers));
    memset(vm->stack, 0, sizeof(vm->stack));
    memset(vm->memory, 0, sizeof(vm->memory));
}
int vm_load(chip8_vm *vm, const char *filename)
{
    FILE *fp = fopen(filename, "rb");
    if (!fp)
    {
        return 0;
    }
    if (vm)
    {
        return fread(vm->memory + VM_START_ADDRESS, 1, VM_MEMORY_SIZE - VM_START_ADDRESS, fp);
    }
    vm_panic("vm is NULL, Internal Error in vm_load", 6);
    return 0;
}

uint8_t get_byte(chip8_vm *vm, uint16_t address)
{
    if (!vm)
        vm_panic("INTERNAL ERROR - vm NULL", 1);

    if (address >= VM_MEMORY_SIZE)
        vm_panic("Out of bounds memory access in get_byte", 2);

    return vm->memory[address];
}
uint16_t vm_get_instruction(chip8_vm *vm)
{
    // Gets the current instruction at address PC
    return ((unsigned)get_byte(vm, vm->PC) << 8) | get_byte(vm, vm->PC + 1);
}
int vm_advance_program_counter(chip8_vm *vm, uint16_t delta)
{
    if ((vm->PC + delta) < VM_MEMORY_SIZE)
    {
        vm->PC += delta;
        return 1;
    }
    else
    {
        return 0;
    }
}
void vm_panic(const char *message, int exit_code)
{
    printf("Chip-8 VM: Panic - %s\n", message);
    exit(exit_code);
}