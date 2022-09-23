#ifndef CPU_H_
#define CPU_H_
#include <stdint.h>

#include "vm.h"
/*
Executes a single opcode instruction on the given vm by calling the appropriate
function Internally it uses a function pointer table to call the function for
the op
*/
int cpu_execute(chip8_vm *vm, uint16_t op);
#endif