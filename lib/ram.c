#include <ram.h>


static ram_context ram_ctx;


u8 wram_read(u16 addres){
    // printf("WRAM_READ %04X\n",addres);
    if(addres < 0xC000 || addres >= 0xE000){
        UNEXPECTED_ERROR("WRAM_READ!");
    }

    return ram_ctx.wram[addres-0xC000];
}

void wram_write(u16 addres, u8 value){
    // printf("WRAM_WRITE %04X -0xC000 =%04X\n",addres,addres-0xC000);
    if(addres < 0xC000 || addres >= 0xE000){
        UNEXPECTED_ERROR("WRAM_WRITE!");
    }
    ram_ctx.wram[addres-0xC000] = value;
}

u8 hram_read(u16 addres){
    // printf("HRAM_READ %04X\n",addres);
    if(addres < 0xFF80 || addres > 0xFFFE){
        UNEXPECTED_ERROR("HRAM_READ!");
    }

    return ram_ctx.hram[addres-0xFF80];
}

void hram_write(u16 addres, u8 value){
    // printf("HRAM_READ %04X\n",addres);
    if(addres < 0xFF80 || addres > 0xFFFE){
        UNEXPECTED_ERROR("HRAM_WRITE!");
    }

    ram_ctx.hram[addres-0xFF80] = value;
}