#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "cpu.h"
#include "graphics.h"
#include "opcodes.h"
#include "vm.h"

#define SDL_MAIN_HANDLED

#include "sdl2/SDL.h"
extern SDL_Window *window;
extern SDL_Renderer *renderer;
/*
int main(int argc, char *argv[])
{
    graphics_initialize();

    SDL_Event e;
    int is_running = 1;
    chip8_vm vm;
    vm_init(&vm);

    SDL_Rect rects[3];
    rects[0].h = 20;
    rects[0].w = 10;
    rects[0].x = 30;
    rects[0].y = 40;

    rects[1].h = 10;
    rects[1].w = 10;
    rects[1].x = 50;
    rects[1].y = 60;

    rects[2].h = 5;
    rects[2].w = 5;
    rects[2].x = 80;
    rects[2].y = 70;


    while (is_running) {
        if (!is_running) break;
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                is_running = 0;
            }
        }
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);  // white
        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);  // black
        //SDL_RenderDrawRects(renderer,&rects,3);
        SDL_RenderFillRects(renderer, &rects, 3);
        SDL_RenderPresent(renderer);
    }
    graphics_close();
}
*/
void handle_keyboard(chip8_vm *vm, SDL_Event e, int *is_running)
{
    if (e.type == SDL_QUIT) *is_running = 0;
    if (e.type == SDL_KEYDOWN) {
        // Simple approach to keyboard, just to experiment
        switch (e.key.keysym.sym) {
            case SDLK_0:
                vm->last_key_pressed = 0;
                break;
            case SDLK_1:
                vm->last_key_pressed = 1;
                break;
            case SDLK_2:
                vm->last_key_pressed = 2;
                break;
            case SDLK_3:
                vm->last_key_pressed = 3;
                break;
            case SDLK_4:
                vm->last_key_pressed = 4;
                break;
            case SDLK_5:
                vm->last_key_pressed = 5;
                break;
            case SDLK_6:
                vm->last_key_pressed = 6;
                break;
            case SDLK_7:
                vm->last_key_pressed = 7;
                break;
            case SDLK_8:
                vm->last_key_pressed = 8;
                break;
            case SDLK_9:
                vm->last_key_pressed = 9;
                break;
            case SDLK_a:
                vm->last_key_pressed = 0xa;
                break;
            case SDLK_b:
                vm->last_key_pressed = 0xb;
                break;
            case SDLK_c:
                vm->last_key_pressed = 0xc;
                break;
            case SDLK_d:
                vm->last_key_pressed = 0xd;
                break;
            case SDLK_e:
                vm->last_key_pressed = 0xe;
                break;
            case SDLK_f:
                vm->last_key_pressed = 0xf;
                break;
            default:
                return;
        }
        vm->is_blocking = 0;
        printf("KEyboard state\n");
        for(int i = 0; i < 16; i++)
        {
            printf("[%d](%u) ", i, vm->keyboard_state[i]);
        }
        printf("================\n");
    }
}
int main(int argc, char *argv[])
{
    int bytes_loaded = 0;
    int mode = 1;
    if (argc != 2) {
        printf("Usage: ./chip8 rom_file\n");
        if (argc != 3)
            exit(10);
        else
            mode = atoi(argv[2]);
    }
    graphics_initialize(64, 32);

    SDL_Event e;

    uint16_t opcode = 0;
    // Check if the rom file name is given or not
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
    printf("ROM name: %s\n", argv[1]);
    printf("Bytes loaded: %d\n", bytes_loaded);
    // For the test suite
    set_verbose();
    // vm.memory[511] = mode;
    //  Loop over all the instructions and execute them
    /*
    SDL_Rect rects[VM_GRAPHICS_WIDTH*VM_GRAPHICS_HEIGHT];
    #define CELL_SIZE 15
    for(int i = 0; i < VM_GRAPHICS_HEIGHT * VM_GRAPHICS_WIDTH; i++)
    {
        rects[i].h = CELL_SIZE-1;
        rects[i].w = CELL_SIZE-1;
        rects[i].x = (i % VM_GRAPHICS_WIDTH) * CELL_SIZE;
        rects[i].y = (i / VM_GRAPHICS_WIDTH) * CELL_SIZE;
    }
    */
    update_rects(vm.graphics_memory, sizeof(vm.graphics_memory),
                 VM_GRAPHICS_WIDTH);

    int is_running = 1;
    do {
        while (SDL_PollEvent(&e)) {
            handle_keyboard(&vm, e, &is_running);
        }


        if (!is_running) break;
        if (vm.is_dirty) {
            clear_screen();
            update_rects(vm.graphics_memory, sizeof(vm.graphics_memory),
                         VM_GRAPHICS_WIDTH);
            display_rects();
            present();
            vm.is_dirty = 0;
        }
        vm_reset_keyboard(&vm);
        SDL_PumpEvents();
        uint8_t *keys = SDL_GetKeyboardState(NULL);
        if(keys[SDLK_0])
            vm.keyboard_state[0] = 1;
        if(keys[SDLK_1])
            vm.keyboard_state[1] = 1;
        if(keys[SDLK_2])
            vm.keyboard_state[2] = 1;
        if(keys[SDLK_3])
            vm.keyboard_state[3] = 1;
        if(keys[SDLK_4])
            vm.keyboard_state[4] = 1;
        if(keys[SDLK_5])
            vm.keyboard_state[5] = 1;
        if(keys[SDLK_6])
            vm.keyboard_state[6] = 1;
        if(keys[SDLK_7])
            vm.keyboard_state[7] = 1;
        if(keys[SDLK_8])
            vm.keyboard_state[8] = 1;
        if(keys[SDLK_9])
            vm.keyboard_state[9] = 1;
        if(keys[SDLK_a])
            vm.keyboard_state[0xa] = 1;
        if(keys[SDLK_b])
            vm.keyboard_state[0xb] = 1;
        if(keys[SDLK_c])
            vm.keyboard_state[0xc] = 1;
        if(keys[SDLK_d])
            vm.keyboard_state[0xd] = 1;
        if(keys[SDLK_e])
            vm.keyboard_state[0xe] = 1;
        if(keys[SDLK_f])
            vm.keyboard_state[0xf] = 1;

        opcode = vm_get_instruction(&vm);
        if (cpu_execute(&vm, opcode) == 0) {
            if (verbose_enabled) {
                printf("| 0x%0*x | 0x%0*x | ", HEX_DISPLAY_SIZE, vm.PC,
                       HEX_DISPLAY_SIZE, opcode);
                printf("Unknown OP Code\n");
            }
        }

        uint8_t prevblk = vm.is_blocking;

        while (vm.is_blocking) {
            while (SDL_PollEvent(&e)) {
                handle_keyboard(&vm, e, &is_running);
            }
        }
        if (prevblk == 1) {
            vm_advance_program_counter(&vm, 2);
            cpu_execute(&vm, opcode);
        }


    } while (vm_advance_program_counter(&vm, 2));// &&
             //(vm.PC - VM_START_ADDRESS) < bytes_loaded);
    graphics_close();
    return 0;
}