#ifndef GRAPHICS_H_
#define GRAPHICS_H_
#define SDL_MAIN_HANDLED
#define CELL_SIZE 15
#define BOX_SIZE 15
#include "sdl2/SDL.h"


// Initialize the SDL2 graphics library, window and renderer
int graphics_initialize(int width, int height);
void clear_screen();
void present();
void update_rects(uint8_t *point_arry, size_t n, int width);
void display_rects();
int graphics_close();
#endif