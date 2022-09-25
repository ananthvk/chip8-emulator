#include "opcodes.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "opcodes_8xxx.h"

// The opcode function pointer table
// This function pointer array stores the function corresponding to a opcode's
// identification In op_table, the first 4 bits are used to determine the
// function to call. In op_8xxx_table, the last 4 bits are used to determine the
// function to call.
op_fptr op_table[] = {
    op_0xxx, op_1xxx, op_2xxx, op_3xxx, op_4xxx, op_5xxx, op_6xxx, op_7xxx,
    op_8xxx, op_9xxx, op_axxx, op_bxxx, op_cxxx, op_dxxx, op_exxx, op_fxxx,
};

op_fptr op_8xxx_table[] = {
    op_8xxx_0, op_8xxx_1, op_8xxx_2, op_8xxx_3, op_8xxx_4, op_8xxx_5,
    op_8xxx_6, op_8xxx_7, op_NOP,    op_NOP,    op_NOP,    op_NOP,
    op_NOP,    op_NOP,    op_8xxx_E, op_NOP,
};

// These functions return 1 if the opcode execution was successful
// otherwise returns 0.

int op_NOP(opcode_args arg)
{
    verbose_opcode(arg.vm, arg.op, "NOP");
    return 0;
}

int op_0xxx(opcode_args arg)
{
    if (arg.op == 0x0000) {
        return op_NOP(arg);
    }
    else if (arg.op == 0x00E0) {
        verbose_opcode(arg.vm, arg.op, "clear display");
        memset(arg.vm->graphics_memory, 0, sizeof(arg.vm->graphics_memory));
        return 1;
    }
    else if (arg.op == 0x00E0) {
        // The stack pointer points to one element above the last stored address
        verbose_opcode(arg.vm, arg.op, "return");
        if (arg.vm->SP > 0) {
            arg.vm->PC = arg.vm->stack[--(arg.vm->SP)];
            return 1;
        }
        else {
            // The stack is empty
            vm_panic("Invalid return statement", 9);
            return 0;
        }
    }
    else {
        verbose_opcode(arg.vm, arg.op, "call machine code @ 0x%0*x",
                       HEX_DISPLAY_SIZE, arg.NNN);
        return 1;
    }
}

int op_1xxx(opcode_args arg)
{
    verbose_opcode(arg.vm, arg.op, "goto 0x%0*x", HEX_DISPLAY_SIZE, arg.NNN);

    if (arg.NNN == 0 || arg.NNN < 512) {
        vm_panic("Invalid goto, less than to 512", 9);
    }
    arg.vm->PC = arg.NNN - 2;
    return 1;
}

int op_2xxx(opcode_args arg)
{
    verbose_opcode(arg.vm, arg.op, "call subroutine @ 0x%0*x", HEX_DISPLAY_SIZE,
                   arg.NNN);
    if (arg.vm->SP == VM_STACK_SIZE) {
        vm_panic("Max stack size reached", 9);
    }
    else {
        arg.vm->stack[arg.vm->SP++] = arg.vm->PC;
        // I am subtracting 2 from program counter, since when the next
        // instruction gets executed The instruction at NNN does not get
        // executed The only issue is if unsigned overflow incase NNN = 0 (which
        // should not happen as programs start at location 512)
        if (arg.NNN == 0 || arg.NNN < 512) {
            vm_panic("Invalid call subroutine instruction, location < 512", 9);
        }
        arg.vm->PC = arg.NNN - 2;
    }
    return 1;
}

int op_3xxx(opcode_args arg)
{
    verbose_opcode(arg.vm, arg.op, "if (V%u == %u) skip", arg.X, arg.NN);
    if (arg.vm->registers[arg.X] == arg.NN) {
        // Skip executing the next instruction
        arg.vm->PC += 2;
    }
    return 1;
}

int op_4xxx(opcode_args arg)
{
    verbose_opcode(arg.vm, arg.op, "if (V%u != %u) skip", arg.X, arg.NN);
    if (arg.vm->registers[arg.X] != arg.NN) {
        // Skip executing the next instruction
        arg.vm->PC += 2;
    }
    return 1;
}

int op_5xxx(opcode_args arg)
{
    if (get_constant_N(arg.op) == 0) {
        verbose_opcode(arg.vm, arg.op, "if (V%u == V%u) skip", arg.X, arg.Y);
        if (arg.vm->registers[arg.X] == arg.vm->registers[arg.Y]) {
            // Skip executing the next instruction
            arg.vm->PC += 2;
        }
        return 1;
    }
    return 0;
}

int op_6xxx(opcode_args arg)
{
    verbose_opcode(arg.vm, arg.op, "V%u = %u", arg.X, arg.NN);
    arg.vm->registers[arg.X] = arg.NN;
    return 1;
}

int op_7xxx(opcode_args arg)
{
    verbose_opcode(arg.vm, arg.op, "V%u += %u", arg.X, arg.NN);
    arg.vm->registers[arg.X] += arg.NN;
    return 1;
}
int op_8xxx(opcode_args arg)
{
    return (*op_8xxx_table[get_constant_N(arg.op)])(arg);
}

int op_9xxx(opcode_args arg)
{
    if (get_constant_N(arg.op) == 0) {
        verbose_opcode(arg.vm, arg.op, "if (V%u != V%u) skip", arg.X, arg.Y);

        if (arg.vm->registers[arg.X] != arg.vm->registers[arg.Y]) {
            // Skip executing the next instruction
            arg.vm->PC += 2;
        }

        return 1;
    }
    return 0;
}

int op_axxx(opcode_args arg)
{
    verbose_opcode(arg.vm, arg.op, "I = 0x%0*x", HEX_DISPLAY_SIZE, arg.NNN);
    if (arg.NNN == 0 || arg.NNN < 510) {
        vm_panic("Invalid set I to address, location < 512", 9);
    }
    if (arg.NNN == 511) {
        printf("WARNING: Setting I = 511\n");
    }
    arg.vm->I = arg.NNN;
    return 1;
}

int op_bxxx(opcode_args arg)
{
    verbose_opcode(arg.vm, arg.op, "PC = V0 + %u", arg.NNN);

    arg.vm->PC = arg.vm->registers[0] + arg.NNN;
    // TODO: Check if this overflows
    arg.vm->PC -= 2;
    // As after jumping, PC is incremented in main and instruction at PC is
    // omitted
    return 1;
}

int op_cxxx(opcode_args arg)
{
    verbose_opcode(arg.vm, arg.op, "V%u = rand() & %u", arg.X, arg.NN);
    arg.vm->registers[arg.X] = (rand() % 255) & arg.NN;
    return 1;
}

void draw_bits(opcode_args arg, int x, int y, uint8_t line)
{
    // Draw a row of bits with width 8 starting at x,y
    int array_index = 0;
    uint8_t last_bit;
    int bitflip_occured = 0;
    for (int i = 7; i >= 0; i--) {
        // Extract each bit from the left, by creating a mask using left shift
        // Modulo VM_GRAPHICS_WIDTH so that if printing near the edge of the
        // screen, the pixel wraps to the other side
        array_index =
            (VM_GRAPHICS_WIDTH * y) + ((x + (7 - i)) % VM_GRAPHICS_WIDTH);
        last_bit = arg.vm->graphics_memory[array_index];
        arg.vm->graphics_memory[array_index] ^= line & (1 << i);
        if ((last_bit == 1) && (arg.vm->graphics_memory[array_index] == 1)) {
            // Bit flip has occured from set to unset
            bitflip_occured = 1;
            // printf("Bit filp occured\n");
        }
    }
    if (bitflip_occured)
        arg.vm->registers[0xF] = 1;
    else
        arg.vm->registers[0xF] = 0;
}

int op_dxxx(opcode_args arg)
{
    // As I does not change after executing this code
    uint16_t I = arg.vm->I;
    // To store a single row of 8 bits
    uint8_t line = 0;
    verbose_opcode(arg.vm, arg.op, "draw(V%u, V%u, %u)", arg.X, arg.Y, arg.N);
    uint8_t x = arg.vm->registers[arg.X];
    uint8_t y = arg.vm->registers[arg.Y];
    for (int i = 0; i < arg.N; i++) {
        line = arg.vm->memory[I + i];
        // printf("%d\n",line);
        draw_bits(arg, x, y + i, line);
    }
    arg.vm->is_dirty = 1;
    return 1;
}

int op_exxx(opcode_args arg)
{
    if (arg.NN == 0x9E) {
        verbose_opcode(arg.vm, arg.op, "if (key() == V%u) skip", arg.X);
        int key = arg.vm->registers[arg.X];
        if (arg.vm->keyboard_state[key] == 1) {
            // The key is in pressed state, skip the current line
            arg.vm->PC += 2;
        }
        return 1;
    }
    else if (arg.NN == 0xA1) {
        verbose_opcode(arg.vm, arg.op, "if (key() != V%u) skip", arg.X);
        int key = arg.vm->registers[arg.X];
        if (arg.vm->keyboard_state[key] == 0) {
            // The key is not in pressed state, skip the current line
            arg.vm->PC += 2;
        }
        return 1;
    }
    else {
        return 0;
    }
}

int op_fxxx(opcode_args arg)
{
    switch (arg.NN) {
        case 0x07:
            // When getting the value of the delay timer, decrement the value of
            // the delay timer according to the timestamp
            verbose_opcode(arg.vm, arg.op, "V%u = get_delay()", arg.X);
            time_t now = time(NULL);
            time_t time_elapsed = now - arg.vm->delay_timer_timestamp;
            // Every 16.6 ms, the counter has to be decremented for a refresh
            // rate of 60Hz
            // arg.vm->timer_delay -= (time_elapsed/16.6);
            int reductions = arg.vm->timer_delay - (time_elapsed / 16.6);
            arg.vm->registers[arg.X] = (reductions <= 0) ? 0 : reductions;
            break;
        case 0x0A:
            verbose_opcode(arg.vm, arg.op, "V%u = get_key()", arg.X);
            if(arg.vm->last_key_pressed < 16)
            {
                // A valid key was pressed
                arg.vm->registers[arg.X] = arg.vm->last_key_pressed;
                arg.vm->is_blocking = 0;
                arg.vm->last_key_pressed = 20;
            }
            else
            {
                // wait for the next keypress
                arg.vm->is_blocking = 1;
                // To re-execute this opcode when a key press arives
                arg.vm->PC -= 2;
            }
            break;
        case 0x15:
            verbose_opcode(arg.vm, arg.op, "delay_timer(V%u)", arg.X);
            // Set the value of the delay timer
            arg.vm->timer_delay = arg.vm->registers[arg.X];
            arg.vm->delay_timer_timestamp = time(NULL);
            break;
        case 0x18:
            verbose_opcode(arg.vm, arg.op, "sound_timer(V%u) NOT_IMPL", arg.X);
            break;
        case 0x1E:
            verbose_opcode(arg.vm, arg.op, "I += V%u", arg.X);
            arg.vm->I += arg.vm->registers[arg.X];
            break;
        case 0x29:
            verbose_opcode(arg.vm, arg.op, "I = sprite_addr[V%u]", arg.X);
            uint8_t X = arg.vm->registers[arg.X];
            if (X > 15) {
                printf("X is %u\n", X);
                vm_panic(
                    "Invalid I = sprite_address(), X Not less than equal 15",
                    9);
            }
            arg.vm->I = VM_SPRITE_ADDRESS + (X * 5);
            break;
        case 0x33:
            verbose_opcode(arg.vm, arg.op,
                           "store BCD of V%u at I(0x%0*x), I+1, I+2", arg.X,
                           HEX_DISPLAY_SIZE, arg.vm->I);
            uint8_t val = arg.vm->registers[arg.X];
            arg.vm->memory[arg.vm->I] = val / 100;
            arg.vm->memory[arg.vm->I + 1] = (val / 10) % 10;
            arg.vm->memory[arg.vm->I + 2] = val % 10;
            break;
        case 0x55:
            verbose_opcode(arg.vm, arg.op,
                           "Store V0 to V%u at address I(0x%0*x)", arg.X,
                           HEX_DISPLAY_SIZE, arg.vm->I);
            // I have not added any error checking here
            for (int i = 0; i <= arg.X; i++) {
                arg.vm->memory[arg.vm->I + i] = arg.vm->registers[i];
            }
            break;
        case 0x65:
            verbose_opcode(arg.vm, arg.op,
                           "Fill V0 to V%u, from address I(0x%0*x)", arg.X,
                           HEX_DISPLAY_SIZE, arg.vm->I);
            for (int i = 0; i <= arg.X; i++) {
                arg.vm->registers[i] = arg.vm->memory[arg.vm->I + i];
            }
            break;

        default:
            return 0;
    }
    return 1;
}
