#include <stdio.h>
#include <stdlib.h>

#include "cpu.h"
#include "opcodes.h"
#include "vm.h"
int main(int argc, char *argv[])
{
    int bytes_loaded = 0;

    uint16_t opcode = 0;
    // Check if the rom file name is given or not
    if (argc != 2) {
        printf("Usage: ./chip8 rom_file\n");
        exit(10);
    }
    // Initialize and load the memory of the VM
    chip8_vm vm;
    vm_init(&vm);
    if (!(bytes_loaded = vm_load(&vm, argv[1]))) {
        printf("%d", bytes_loaded);
        vm_panic(
            "Unable to read ROM file. Either the file does not exist or is not "
            "valid\n",
            5);
    }
    // Loop over all the instructions and execute them
    do {
        opcode = vm_get_instruction(&vm);
        if (cpu_execute(&vm, opcode) == 0) {
            printf("| 0x%0*x | 0x%0*x | ", HEX_DISPLAY_SIZE, vm.PC,
                   HEX_DISPLAY_SIZE, opcode);
            printf("Unknown OP Code\n");
        }

    } while (vm_advance_program_counter(&vm, 2) &&
             (vm.PC - VM_START_ADDRESS) < bytes_loaded);
    return 0;
}