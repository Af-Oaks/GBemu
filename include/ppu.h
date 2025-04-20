#pragma once

#include <common.h>



typedef struct 
{
    u8 y;    //
    u8 x;    //
    u8 tile; //
    u8 flags;//
}oam_entry;

typedef struct 
{
    oam_entry oam_ram[0x40];
    u8 vram[0x2000];
}ppu_context;



void ppu_init();
void ppu_tick();
void ppu_vram_write(u16 address, u8 value);
u8 ppu_vram_read(u16 address);
void ppu_oam_write(u16 address, u8 value);
u8 ppu_oam_read(u16 address);