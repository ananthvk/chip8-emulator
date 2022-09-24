#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

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

int main(int argc, char *argv[])
{
    int bytes_loaded = 0;
    if (argc != 2) {
        printf("Usage: ./chip8 rom_file\n");
        exit(10);
    }
    graphics_initialize();

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
    verbose_enabled = 1;
    // Loop over all the instructions and execute them
    int to_execute;
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
   update_rects(vm.graphics_memory, sizeof(vm.graphics_memory));

    int cursor_x = 0;
    int cursor_y = 0;

    int is_running = 1;
    do {
        to_execute = 0;
        // Infinite loop to prevent execution
        while (!to_execute) {
            if (!is_running) break;
            while (SDL_PollEvent(&e)) {
                if (!is_running) break;
                if (e.type == SDL_QUIT) {
                    is_running = 0;
                }
                else if (e.type == SDL_KEYDOWN) {
                    switch (e.key.keysym.sym) {
                        case SDLK_e:
                            to_execute = 1;
                            break;
                        case SDLK_d:
                            printf("Doing it %d++", cursor_x);
                            cursor_x ++;
                            vm.graphics_memory[cursor_x + (VM_GRAPHICS_WIDTH * cursor_y)] = 1;
                            break;
                        case SDLK_a:
                            printf("Doing it %d--", cursor_x);
                            cursor_x --;
                            vm.graphics_memory[cursor_x + (VM_GRAPHICS_WIDTH * cursor_y)] = 1;
                            break;
                    }
                }
            }

            clear_screen();
            update_rects(vm.graphics_memory, sizeof(vm.graphics_memory));
            display_rects();
            present();

        }
        if (!is_running) break;
        opcode = vm_get_instruction(&vm);
        if (cpu_execute(&vm, opcode) == 0) {
            if (verbose_enabled) {
                printf("| 0x%0*x | 0x%0*x | ", HEX_DISPLAY_SIZE, vm.PC,
                       HEX_DISPLAY_SIZE, opcode);
                printf("Unknown OP Code\n");
            }
        }

    } while (vm_advance_program_counter(&vm, 2) &&
             (vm.PC - VM_START_ADDRESS) < bytes_loaded);
    graphics_close();
    return 0;
}