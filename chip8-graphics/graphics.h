#ifndef GRAPHICS_H_
#define GRAPHICS_H_
#define SDL_MAIN_HANDLED
#include "sdl2/SDL.h"

extern SDL_Window *window;
extern SDL_Renderer *renderer;

// Initialize the SDL2 graphics library, window and renderer
int graphics_initialize();

int graphics_close();
#endif