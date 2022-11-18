#include <stdlib.h>
#include <SDL2/SDL.h>

#include "display.h"

Display *init_display(int scale) {
  Display *display = malloc(sizeof(Display));
  if (!display) {
    return NULL;
  }

  display->memory = malloc(ROWS * COLS * sizeof(bool));
  if (!display->memory) {
    return NULL;
  }

  display->window = SDL_CreateWindow( "chip7", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, COLS*scale, ROWS*scale, SDL_WINDOW_SHOWN );
  if (display->window == NULL) {
    return NULL;
  }

  display->surface = SDL_GetWindowSurface(display->window);
  if (display->window == NULL) {
    return NULL;
  }

  display->scale = scale;
  display->rows = ROWS;
  display->cols = COLS;

  return display;
}
