#include <SDL2/SDL.h>
#include <stdio.h>
#include "display.h"

int main(int argc, char *argv[]) {
  if( SDL_Init( SDL_INIT_VIDEO ) < 0 ) {
      printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
      exit(1);
  }

  Display *display = init_display(10);
  if (display == NULL) {
    printf("Failed to initialize display\n");
    exit(1);
  }
  draw_pixel(display, 0, 0);
  draw_pixel(display, 1, 1);
  render(display);

  bool quit = false;
  SDL_Event e;

  while(!quit) {
    while( SDL_PollEvent( &e ) != 0 ) {
      if( e.type == SDL_QUIT ) {
        quit = true;
      }
    }
  }
}

