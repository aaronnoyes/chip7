#ifndef CPU_H
#define CPU_H

#include <stdint.h>

#include "display.h"
#include "keyboard.h"

typedef struct CPU {
    Keyboard *keyboard;
    Display *display;
    uint8_t *memory;
    uint8_t v[16];
    int last_x;
    int i;
    int delayTimer, soundTimer;
    int pc;
    uint16_t stack[64];
    int stackptr;
    bool paused;
} CPU;

CPU *init_cpu(Display *display, Keyboard *keyboard);
int load_font_sprites(CPU *cpu);
void load_rom(CPU *cpu, char romName[]);
void update_timers(CPU *cpu);
void cycle(CPU *cpu);
void execute_instruction(CPU *cpu, uint16_t opcode);

#endif
