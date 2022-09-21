#ifndef CPU_H_
#define CPU_H_
#include "vm.h"
#include<stdint.h>
// NOTE: I have not bothered to check if vm is NULL in the code as it is expected that vm is non-NULL
int cpu_execute(chip8_vm *vm, uint16_t op);
#endif