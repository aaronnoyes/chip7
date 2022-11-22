#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <stdint.h>
#include <SDL2/SDL.h>

#include "cpu.h"

#define NUMKEYS 16

typedef struct Keyboard {
  uint8_t keys_pressed[NUMKEYS];
  void (*on_next_key_press)(CPU *,int);
} Keyboard;

Keyboard *init_keyboard();
uint8_t get_key_value(SDL_KeyCode key);
void on_key_down(Keyboard *keyboard, uint8_t key);
void on_key_up(Keyboard *keyboard, uint8_t key);

#endif
