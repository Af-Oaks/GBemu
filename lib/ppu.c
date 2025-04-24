#include <ppu.h>
#include <lcd.h>

static ppu_context ctx;

void ppu_init() {

}

void ppu_tick() {

}

void ppu_render(){
    for(int x=0;x<144;x++){//horizontal mode
        //mode 2 OAM scan
    
        //mode 3 Drawing pixel
        for(int x=0;x<160;x++){

        }

        //mode 0 horizontal blank
    }

    for(int x=0;x<10;x++){//vertical mode?
        //mode 1
        for(int x=0;x<160;x++){
            
        }

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