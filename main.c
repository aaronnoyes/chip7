#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <stdio.h>

#include "display.h"
#include "cpu.h"
#include "keyboard.h"

int main(int argc, char *argv[]) {
  time_t t;

  if( SDL_Init( SDL_INIT_VIDEO ) < 0 ) {
      printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
      exit(1);
  }

  Keyboard *keyboard = init_keyboard();
  if (!keyboard) {
    printf("Failed to initialize keyboard\n");
    exit(1);
  }

  Display *display = init_display(10);
  if (!display) {
    printf("Failed to initialize display\n");
    exit(1);
  }

  CPU *cpu = init_cpu(display, keyboard);
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
      else if (e.type == SDL_KEYDOWN) {
        int key = get_key_value(e.key.keysym.sym);
        on_key_down(keyboard, key);
      }
      else if (e.type == SDL_KEYUP) {
        int key = get_key_value(e.key.keysym.sym);
        on_key_up(keyboard, key);
      }
    }
    cycle(cpu);
    update_timers(cpu);
    render(display);
  }
}

