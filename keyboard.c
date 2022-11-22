#include <stdint.h>
#include <SDL2/SDL.h>
#include <stdbool.h>

#include "keyboard.h"
#include "cpu.h"

Keyboard *init_keyboard() {
  Keyboard *keyboard = malloc(sizeof(Keyboard));

  for (int i = 0; i < NUMKEYS; i++) {
    keyboard->keys_pressed[i] = 0;
  }

  keyboard->on_next_key_press = NULL;

  return keyboard;
}

uint8_t get_key_value(SDL_KeyCode key) {
  switch (key) {
    case SDLK_1:
      return 0x1;
      break;
    case SDLK_2:
      return 0x2;
      break;
    case SDLK_3:
      return 0x3;
      break;
    case SDLK_4:
      return 0xC;
      break;
    case SDLK_q:
      return 0x4;
      break;
    case SDLK_w:
      return 0x5;
      break;
    case SDLK_e:
      return 0x6;
      break;
    case SDLK_r:
      return 0xD;
      break;
    case SDLK_a:
      return 0x7;
      break;
    case SDLK_s:
      return 0x8;
      break;
    case SDLK_d:
      return 0x9;
      break;
    case SDLK_f:
      return 0xE;
      break;
    case SDLK_z:
      return 0xA;
      break;
    case SDLK_x:
      return 0x0;
      break;
    case SDLK_c:
      return 0xB;
      break;
    case SDLK_v:
      return 0xF;
      break;
    default:
      return -1;
      break;
  }
}


void on_key_down(Keyboard *keyboard, uint8_t key) {
  keyboard->keys_pressed[key] = true; 
  if (keyboard->on_next_key_press != NULL && key) {
    keyboard->on_next_key_press(key);
    keyboard->on_next_key_press = NULL;
  }
}

void on_key_up(Keyboard *keyboard, uint8_t key) {
  keyboard->keys_pressed[key] = false; 
}
