#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <stdint.h>
#include <SDL2/SDL.h>

#define NUMKEYS 16

typedef struct Keyboard {
  uint8_t keys_pressed[NUMKEYS];
} Keyboard;

Keyboard *init_keyboard();
uint8_t get_key_value(SDL_KeyCode key);

#endif
