#include <stdlib.h>
#include <SDL2/SDL.h>

#include "display.h"

Display *init_display(int scale) {
  Display *display = malloc(sizeof(Display));
  if (!display) {
    return NULL;
  }

  display->memory = calloc(ROWS * COLS, sizeof(bool));
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

bool draw_pixel(Display *display, int x, int y) {
  x = x % 64;
  y = y % 32;
  int pixel = x + y*COLS;
  display->memory[pixel] = !display->memory[pixel];
  return !display->memory[pixel];
}

void clear(Display *display) {
  for(int i = 0; i < ROWS*COLS; i++) {
    display->memory[i] = 0;
  }
}

void render(Display *display) {
  int x = 0, y = 0;
  SDL_Rect r;
  r.w = display->scale;
  r.h = display->scale;
  Uint32 black = SDL_MapRGB(display->surface->format, 0x00, 0x00, 0x00);
  Uint32 white = SDL_MapRGB(display->surface->format, 0xff, 0xff, 0xff);

  SDL_FillRect(display->surface, NULL, white);

  for (int i = 0; i < COLS*ROWS; i++) {
    x = i % COLS;
    y = (int) i / COLS;
    if (display->memory[i]) {
      r.x = x*display->scale;
      r.y = y*display->scale;
      SDL_FillRect(display->surface, &r, black);
    }
  }
  SDL_UpdateWindowSurface(display->window);
}