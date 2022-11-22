#include <SDL2/SDL.h>
#include <stdio.h>

#include "display.h"
#include "cpu.h"

int main(int argc, char *argv[]) {
  time_t t;

  if( SDL_Init( SDL_INIT_VIDEO ) < 0 ) {
      printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
      exit(1);
  }

  Display *display = init_display(10);
  if (!display) {
    printf("Failed to initialize display\n");
    exit(1);
  }

  CPU *cpu = init_cpu(display);
  if (!cpu) {
    printf("Failed to initialize CPU\n");
    exit(1); 
  }
  load_font_sprites(cpu);
  load_rom(cpu, "roms/BLITZ");

  srand((unsigned) time(&t));

  bool quit = false;
  SDL_Event e;

  while(!quit) {
    while( SDL_PollEvent( &e ) != 0 ) {
      if( e.type == SDL_QUIT ) {
        quit = true;
      }
    }
    cycle(cpu);
    render(display);
  }
}

