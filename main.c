#include <stdio.h>
#include <stdlib.h>

#include "cpu.h"
#include "opcodes.h"
#include "vm.h"
#define SDL_MAIN_HANDLED

#include "sdl2/SDL.h"

int main(int argc, char *argv[])
{
    int bytes_loaded = 0;

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        vm_panic("Unable to initialize graphics library", 16);
    }
    SDL_Window *window =
        SDL_CreateWindow("CHIP 8 - VirtualMachine", SDL_WINDOWPOS_CENTERED,
                         SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_SHOWN);
    if (!window) {
        printf("SDL Error: %s\n", SDL_GetError());
        vm_panic("SDL Error", 16);
    }
    SDL_Renderer *renderer = SDL_CreateRenderer(
        window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!renderer) {
        printf("SDL Error: %s\n", SDL_GetError());
        vm_panic("SDL Error", 16);
    }
    SDL_Event e;

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
    verbose_enabled = 1;
    // Loop over all the instructions and execute them
    int to_execute;
    SDL_Rect rect;
    rect.h = 10;
    rect.w = 10;
    rect.x = 5;
    rect.y = 7;
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
                        case SDLK_w:
                            rect.y -= 10;
                            break;
                        case SDLK_a:
                            rect.x -= 10;
                            break;
                        case SDLK_s:
                            rect.y += 10;
                            break;
                        case SDLK_d:
                            rect.x += 10;
                            break;
                        case SDLK_h:
                            rect.w -= 10;
                            if(rect.w < 0) rect.w = 0;
                            break;
                         case SDLK_j:
                            rect.h += 10;
                            break;
                        case SDLK_k:
                            rect.h -= 10;
                            if(rect.h < 0) rect.h = 0;
                            break;
                         case SDLK_l:
                            rect.w += 10;
                            break;
                        case SDLK_ESCAPE:
                            is_running = 0;
                            break;
                    }
                }
            }
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);  // white
            SDL_RenderClear(renderer);
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            // SDL_RenderDrawRect(renderer, &rect);
            SDL_RenderFillRect(renderer, &rect);
            SDL_RenderPresent(renderer);
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
    return 0;
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}