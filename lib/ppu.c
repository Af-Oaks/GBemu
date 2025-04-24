#include <ppu.h>
#include <lcd.h>

static ppu_context ctx;

void ppu_init() {

    lcd_init();
    LCDS_MODE_SET(MODE_OAM);

    memset(ctx.oam_ram, 0, sizeof(ctx.oam_ram));
}

void ppu_tick() {
    ctx.line_ticks++;

    switch(LCDS_MODE) {
    case MODE_OAM:
        ppu_mode_oam();
        break;
    case MODE_XFER:
        ppu_mode_xfer();
        break;
    case MODE_VBLANK:
        ppu_mode_vblank();
        break;
    case MODE_HBLANK:
        ppu_mode_hblank();
        break;
    }
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