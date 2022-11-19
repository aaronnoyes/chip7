#ifndef DISPLAY_H
#define DISPLAY_H

#include <stdbool.h>
#include <SDL2/SDL.h>

#define ROWS 32
#define COLS 64

typedef struct Display {
  int rows;
  int cols;
  int scale;
  bool *memory;
  SDL_Window *window;
  SDL_Surface *surface;
} Display;

Display *init_display(int scale);
bool draw_pixel(Display *display, int x, int y);
void clear(Display *display);
void render(Display *display);

#endif
