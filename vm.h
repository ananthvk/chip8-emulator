#ifndef VM_H_
#define VM_H_
#include<stdint.h>

// Memory limit for the VM, should not exceed 65535
// as PC, program counter is 16 bits unsigned integer
#define VM_MEMORY_SIZE 4096
// Location 512
#define VM_START_ADDRESS 0x200
#define VM_NUMBER_OF_REGISTERS 16
// Stack size for the VM, should not exceed 255 
// as stack pointer is 8 bits and its max value is 255
#define VM_STACK_SIZE 16


struct chip8_vm{
    // Memory, register and stacks
    uint8_t memory[VM_MEMORY_SIZE];
    uint8_t registers[VM_NUMBER_OF_REGISTERS];
    uint16_t stack[VM_STACK_SIZE];

    // Some other special purpose registers
    uint8_t timer_delay;
    uint8_t timer_sound;
    uint16_t I;
    // Program counter
    uint16_t PC; 
    // Stack pointer
    uint8_t SP;
};

typedef struct chip8_vm chip8_vm;

void vm_init(chip8_vm *vm);
int vm_load(chip8_vm *vm, const char *filename);
uint8_t get_byte(chip8_vm *vm, uint16_t address);
uint16_t vm_get_instruction(chip8_vm *vm);
int vm_advance_program_counter(chip8_vm *vm, uint16_t delta);
void vm_panic(const char *message, int exit_code);
void verbose_opcode(chip8_vm *vm, uint16_t op, const char * format, ...);
#endif