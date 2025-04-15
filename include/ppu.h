#pragma once

#include <common.h>

typedef struct 
{
    u8 vram[0x2000];
}ppu_context;



void ppu_init();
void ppu_tick();
void ppu_vram_write(u16 address, u8 value);
u8 ppu_vram_read(u16 address);