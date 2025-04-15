#include <ppu.h>

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