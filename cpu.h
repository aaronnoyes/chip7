#ifndef CPU_H
#define CPU_H

#include <stdint.h>

#include "display.h"

typedef struct CPU {
    Display *display;
    uint8_t *memory;
    uint8_t v[16];
    int i;
    int delayTimer, soundTimer;
    int pc;
    uint16_t stack[16];
    bool paused;
} CPU;

CPU *init_cpu(Display *display);
int load_font_sprites(CPU *cpu);
void load_rom(CPU *cpu, char romName[]);
void cycle(CPU *cpu);
void execute_instruction(CPU *cpu, uint16_t opcode);

#endif