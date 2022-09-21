#ifndef CPU_H_
#define CPU_H_
#include "vm.h"
#include<stdint.h>

typedef enum ExecStatus{
    EXEC_NOP,
    EXEC_SUCCESS,
    EXEC_FAILURE,
    EXEC_UNKNOWN
} ExecStatus;

// NOTE: I have not bothered to check if vm is NULL in the code as it is expected that vm is non-NULL
// These functions return 1 if any of the instruction was executed.
ExecStatus cpu_execute(chip8_vm *vm, uint16_t op);
#endif