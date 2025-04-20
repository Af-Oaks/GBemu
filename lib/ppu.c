#include <ppu.h>
#include <lcd.h>

static ppu_context ctx;

void ppu_init() {

}

void ppu_tick() {

}

void ppu_vram_write(u16 address, u8 value) {
    ctx.vram[address - 0x8000] = value;
}

u8 ppu_vram_read(u16 address) {
    return ctx.vram[address - 0x8000];
}

void ppu_oam_write(u16 address, u8 value) {
    ((u8*)ctx.oam_ram)[address - 0xFE00] = value;
}

u8 ppu_oam_read(u16 address) {
    return ((u8*)ctx.oam_ram)[address - 0xFE00];
}