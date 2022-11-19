#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "cpu.h"

CPU *init_cpu(Display *display) {
    CPU *cpu = malloc(sizeof(CPU));
    if (!cpu) {
        return NULL;
    }

    cpu->memory = calloc(4096, sizeof(uint8_t));
    if (!cpu->memory) {
        return NULL;
    }

    cpu->pc = 0x200;

    return cpu;
}

int load_font_sprites(CPU *cpu) {
    const uint8_t sprites[] = {
        0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
        0x20, 0x60, 0x20, 0x20, 0x70, // 1
        0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
        0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
        0x90, 0x90, 0xF0, 0x10, 0x10, // 4
        0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
        0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
        0xF0, 0x10, 0x20, 0x40, 0x40, // 7
        0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
        0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
        0xF0, 0x90, 0xF0, 0x90, 0x90, // A
        0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
        0xF0, 0x80, 0x80, 0x80, 0xF0, // C
        0xE0, 0x90, 0x90, 0x90, 0xE0, // D
        0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
        0xF0, 0x80, 0xF0, 0x80, 0x80  // F
    };

    void *success = memcpy(cpu->memory, sprites, sizeof(sprites));
    if (!success) {
        return 1;
    }

    return 0;
}

void load_rom(CPU *cpu, char romName[]) {
    FILE *file = fopen(romName, "rb");
    fseek(file, 0L, SEEK_END);
    long fileSize = ftell(file);
    rewind(file);

    fread(cpu->memory + 0x200, sizeof(uint8_t), fileSize, file);

    fclose(file);
}

void cycle(CPU *cpu) {
    uint16_t opcode = 0;
    if (!cpu->paused) {
       opcode = (cpu->memory[cpu->pc] << 8 | cpu->memory[cpu->pc+1]);
       execute_instruction(cpu, opcode);
    }
}

void execute_instruction(CPU *cpu, uint16_t opcode) {
    cpu->pc += 2;
    uint8_t x = (opcode & 0x0F00) >> 8;
    uint8_t y = (opcode & 0x00F0) >> 4;
    switch (opcode & 0xF000) {
    case 0x0000:
        switch (opcode) {
            case 0x00E0:
                break;
            case 0x00EE:
                break;
        }

        break;
    case 0x1000:
        break;
    case 0x2000:
        break;
    case 0x3000:
        break;
    case 0x4000:
        break;
    case 0x5000:
        break;
    case 0x6000:
        break;
    case 0x7000:
        break;
    case 0x8000:
        switch (opcode & 0xF) {
            case 0x0:
                break;
            case 0x1:
                break;
            case 0x2:
                break;
            case 0x3:
                break;
            case 0x4:
                break;
            case 0x5:
                break;
            case 0x6:
                break;
            case 0x7:
                break;
            case 0xE:
                break;
        }

        break;
    case 0x9000:
        break;
    case 0xA000:
        break;
    case 0xB000:
        break;
    case 0xC000:
        break;
    case 0xD000:
        break;
    case 0xE000:
        switch (opcode & 0xFF) {
            case 0x9E:
                break;
            case 0xA1:
                break;
        }

        break;
    case 0xF000:
        switch (opcode & 0xFF) {
            case 0x07:
                break;
            case 0x0A:
                break;
            case 0x15:
                break;
            case 0x18:
                break;
            case 0x1E:
                break;
            case 0x29:
                break;
            case 0x33:
                break;
            case 0x55:
                break;
            case 0x65:
                break;
        }

        break;

    default:
        printf("Invalid instruction\n");
        exit(1);
}

}