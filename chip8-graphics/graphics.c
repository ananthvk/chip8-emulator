#include "graphics.h"

#include <stdio.h>
#include <stdlib.h>

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;
SDL_Rect *rects = NULL;
size_t n_rects = 0;


int graphics_initialize(int width, int height)
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL Error: %s\n", SDL_GetError());
        exit(16);
    }
    window =
        SDL_CreateWindow("CHIP 8 - VirtualMachine", SDL_WINDOWPOS_CENTERED,
                         SDL_WINDOWPOS_CENTERED, width*CELL_SIZE, height*CELL_SIZE, SDL_WINDOW_SHOWN);
    if (!window) {
        printf("SDL Error: %s\n", SDL_GetError());
        exit(16);
    }
    renderer = SDL_CreateRenderer(
        window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
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
    free(rects);
    SDL_Quit();
    return 1;
}

void clear_screen()
{
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);  // white
    SDL_RenderClear(renderer);
}
void present() { SDL_RenderPresent(renderer); }
void update_rects(uint8_t *point_array, size_t n, int width)
{
    // Sets rects array if NULL otherwise updates the existing rects
    if (!point_array) return;
    if (!rects) {
        rects = malloc(sizeof(SDL_Rect) * n);
        n_rects = n;
        if (!rects) {
            printf("Memory allocation failed!");
            exit(1);
        }
        for (size_t i = 0; i < n; i++) {
            rects[i].h = BOX_SIZE;
            rects[i].w = BOX_SIZE;
            rects[i].x = (i % width) * CELL_SIZE;
            rects[i].y = (i / width) * CELL_SIZE;
        }
    }
    else {
        // Add code to update
        for (size_t i = 0; i < n; i++) {
            if (point_array[i]) {
                rects[i].h = 0;
                rects[i].w = 0;
            }
            else {
                rects[i].h = BOX_SIZE;
                rects[i].w = BOX_SIZE;
            }
        }
    }
}
void display_rects()
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderFillRects(renderer, rects, n_rects);
}