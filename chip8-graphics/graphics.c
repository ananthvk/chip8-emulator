#include "graphics.h"

#include<stdlib.h>
#include<stdio.h>

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;

int graphics_initialize()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL Error: %s\n", SDL_GetError());
        exit(16);
    }
    window = SDL_CreateWindow("CHIP 8 - VirtualMachine", SDL_WINDOWPOS_CENTERED,
                         SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_SHOWN);
    if (!window) {
        printf("SDL Error: %s\n", SDL_GetError());
        exit(16);
    }
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!renderer) {
        printf("SDL Error: %s\n", SDL_GetError());
        exit(16);
    }
    return 1;
}
int graphics_close()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 1;
}