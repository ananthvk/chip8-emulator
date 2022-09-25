#include "vm.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// clang-format off
// stores these sprites from location 16(arbitrary)
// In the main memory
static uint8_t sprites []= {
        0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
        0x20, 0x60, 0x20, 0x20, 0x70, // 1
        0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
        0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
        0x90, 0x90, 0xF0, 0x10, 0x10, // 4
        0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
        0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
        0xF0, 0x10, 0x20, 0x40, 0x40, // 7
        0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
        0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
        0xF0, 0x90, 0xF0, 0x90, 0x90, // A
        0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
        0xF0, 0x80, 0x80, 0x80, 0xF0, // C
        0xE0, 0x90, 0x90, 0x90, 0xE0, // D
        0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
        0xF0, 0x80, 0xF0, 0x80, 0x80  // F
};
// clang-format on
void vm_init(chip8_vm *vm)
{
    vm->PC = VM_START_ADDRESS;
    vm->SP = 0;
    vm->I = 0;
    vm->timer_delay = 0;
    vm->timer_sound = 0;
    vm->last_key_pressed = 20; // Outside the actual range
    vm->delay_timer_timestamp = 0;
    vm->is_dirty = 1;
    vm->is_blocking = 0;
    // Zero all the arrays
    memset(vm->registers, 0, sizeof(vm->registers));
    memset(vm->stack, 0, sizeof(vm->stack));
    memset(vm->memory, 0, sizeof(vm->memory));
    memset(vm->graphics_memory, 0, sizeof(vm->graphics_memory));
    memset(vm->keyboard_state, 0, sizeof(vm->keyboard_state));
    // Copy the sprite data into the main memory
    memcpy(&vm->memory[VM_SPRITE_ADDRESS], &sprites[0], 80);
}
int vm_load(chip8_vm *vm, const char *filename)
{
    FILE *fp = fopen(filename, "rb");
    if (!fp) {
        return 0;
    }
    if (vm) {
        return fread(vm->memory + VM_START_ADDRESS, 1,
                     VM_MEMORY_SIZE - VM_START_ADDRESS, fp);
    }
    vm_panic("vm is NULL, Internal Error in vm_load", 6);
    fclose(fp);
    return 0;
}

uint8_t get_byte(chip8_vm *vm, uint16_t address)
{
    if (!vm) vm_panic("INTERNAL ERROR - vm NULL", 1);

    if (address >= VM_MEMORY_SIZE)
        vm_panic("Out of bounds memory access in get_byte", 2);

    return vm->memory[address];
}
uint16_t vm_get_instruction(chip8_vm *vm)
{
    // Gets the current instruction at address PC
    if (!vm) {
        vm_panic("INTERNAL ERROR - vm NULL", 5);
    }
    return ((unsigned)get_byte(vm, vm->PC) << 8) | get_byte(vm, vm->PC + 1);
}
int vm_advance_program_counter(chip8_vm *vm, uint16_t delta)
{
    if ((vm->PC + delta) < VM_MEMORY_SIZE) {
        vm->PC += delta;
        return 1;
    }
    else {
        return 0;
    }
}
void vm_panic(const char *message, int exit_code)
{
    printf("CRITICAL: Chip-8 VM: Panic - %s\n", message);
    exit(exit_code);
}

void vm_reset_keyboard(chip8_vm *vm)
{
    memset(vm->keyboard_state, 0, sizeof(vm->keyboard_state));
}