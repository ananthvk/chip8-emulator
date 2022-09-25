#ifndef VM_H_
#define VM_H_
#include <stdint.h>

// Memory limit for the VM, should not exceed 65535
// as PC, program counter is 16 bits unsigned integer
#define VM_MEMORY_SIZE 4096
// Location 512
#define VM_START_ADDRESS 0x200
#define VM_STACK_SIZE 16
#define VM_SPRITE_ADDRESS 16 // Arbitrary, keep it below 512-80
#define HEX_DISPLAY_SIZE 4
#define VM_NUMBER_OF_REGISTERS 16
#define VM_GRAPHICS_WIDTH 64
#define VM_GRAPHICS_HEIGHT 32
// Stack size for the VM, should not exceed 255
// as stack pointer is 8 bits and its max value is 255

struct chip8_vm {
    // Memory, register and stacks
    uint8_t memory[VM_MEMORY_SIZE];
    uint8_t registers[VM_NUMBER_OF_REGISTERS];
    uint16_t stack[VM_STACK_SIZE];
    uint8_t graphics_memory[VM_GRAPHICS_HEIGHT * VM_GRAPHICS_WIDTH];

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

// Initialize the vm, by setting all memory and variables to 0
// and setting the program counter(PC) to the start address
void vm_init(chip8_vm *vm);

/*
Loads a rom file into the memory of the given vm
Returns 1 if success, 0 on failure
*/
int vm_load(chip8_vm *vm, const char *filename);

/*
Get a single byte from the memory of the vm at the specified address
*/
uint8_t get_byte(chip8_vm *vm, uint16_t address);

/*
Get a single instruction or two bytes from the location of the program counter
(PC)
*/
uint16_t vm_get_instruction(chip8_vm *vm);

/*
Advances the program counter by the given delta.
If the program counter reaches the end of memory, 0 is returned
*/
int vm_advance_program_counter(chip8_vm *vm, uint16_t delta);

/*
To stop and exit execution of program in case of any serious errors
*/
void vm_panic(const char *message, int exit_code);


#endif