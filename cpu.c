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

    cpu->display = display;

    cpu->stackptr = 0;

    cpu->pc = 0x200;

    cpu->delayTimer = 0;

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

void update_timers(CPU *cpu) {
    if (cpu->delayTimer > 0) {
        cpu->delayTimer -=1;
    }
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
                clear(cpu->display);
                break;
            case 0x00EE:
                cpu->pc = cpu->stack[cpu->stackptr];
                cpu->stackptr--;
                break;
        }

        break;
    case 0x1000:
        cpu->pc = opcode & 0x0FFF;
        break;
    case 0x2000:
        cpu->stackptr++;
        cpu->stack[cpu->stackptr] = cpu->pc;
        cpu->pc = opcode & 0x0FFF;
        break;
    case 0x3000:
        if (cpu->v[x] == opcode & 0x00FF) {
            cpu->pc += 2;
        }
        break;
    case 0x4000:
        if (cpu->v[x] != opcode & 0x00FF) {
            cpu->pc += 2;
        }
        break;
    case 0x5000:
        if (cpu->v[x] == cpu->v[y]) {
            cpu->pc += 2;
        }
        break;
    case 0x6000:
        cpu->v[x] = opcode & 0x00FF;
        break;
    case 0x7000:
        cpu->v[x] = cpu->v[x] + opcode & 0x00FF;
        break;
    case 0x8000:
        switch (opcode & 0xF) {
            case 0x0:
                cpu->v[x] = cpu->v[y];
                break;
            case 0x1:
                cpu->v[x] = cpu->v[x] | cpu->v[y];
                break;
            case 0x2:
                cpu->v[x] = cpu->v[x] & cpu->v[y];
                break;
            case 0x3:
                cpu->v[x] = cpu->v[x] ^ cpu->v[y];
                break;
            case 0x4:
                int x = cpu->v[x] + cpu->v[y];
                cpu->v[0xF] = 0;
                if (x > 255) {
                    cpu->v[0xF] = 1;
                }
                cpu->v[x] = x & 0xFFFF;
                break;
            case 0x5:
                cpu->v[0xF] = 0;
                if (cpu->v[x] > cpu->v[y]) {
                    cpu->v[0xF] = 1;
                }
                cpu->v[x] = cpu->v[x] - cpu->v[y];
                break;
            case 0x6:
                cpu->v[0xF] = cpu->v[x] & 0x1;
                cpu->v[0x0F00] >>= 1;
                break;
            case 0x7:
                cpu->v[0xF] = 0;
                if (cpu->v[x] < cpu->v[y]) {
                    cpu->v[0xF] = 1;
                }
                cpu->v[x] = cpu->v[y] - cpu->v[x];
                break;
            case 0xE:
                cpu->v[0xF] = cpu->v[x] & 0x80;
                cpu->v[0x0F00] <<= 1;
                break;
        }

        break;
    case 0x9000:
        if (cpu->v[x] != cpu->v[x]) {
            cpu->pc += 2;
        }
        break;
    case 0xA000:
        cpu->i = opcode & 0x0FFF;
        break;
    case 0xB000:
        cpu->pc = cpu->v[0] + (opcode & 0x0FFF);
        break;
    case 0xC000:
        uint8_t r = rand() % 256;
        cpu->v[x] = r & (opcode & 0x00FF);
        break;
    case 0xD000:
        int width = 8;
        int height = (opcode & 0xF);

        cpu->v[0xF] = 0;

        for (int row = 0; row < height; row++) {
            int sprite = cpu->memory[cpu->i + row];

            for (int col = 0; col < width; col++) {
                if ((sprite & 0x80) > 0) {
                    if(draw_pixel(cpu->display, cpu->v[x] + col, cpu->v[y] + row)) {
                        cpu->v[0xF] = 1;
                    }
                }

                sprite <<= 1;
            }
        }
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
                cpu->v[x] = cpu->delayTimer;
                break;
            case 0x0A:
                break;
            case 0x15:
                cpu->delayTimer = cpu->v[x];
                break;
            case 0x18:
                break;
            case 0x1E:
                cpu->i += cpu->v[x];
                break;
            case 0x29:
                cpu->i = cpu->v[x] * 5;
                break;
            case 0x33:
                cpu->memory[cpu->i] = (cpu->v[x] / 100);
                cpu->memory[cpu->i + 1] = ((cpu->v[x] % 100) / 10);
                cpu->memory[cpu->i + 2] = (cpu->v[x] % 10);
                break;
            case 0x55:
                for (int registerIndex = 0; registerIndex <= x; registerIndex++) {
                    cpu->memory[cpu->i + registerIndex] = cpu->v[registerIndex];
                }
                break;
            case 0x65:
                for (int registerIndex = 0; registerIndex <= x; registerIndex++) {
                    cpu->v[registerIndex] = cpu->memory[cpu->i + registerIndex];
                }
                break;
        }

        break;

    default:
        printf("Invalid instruction\n");
        exit(1);
}

}