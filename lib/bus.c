#include <bus.h>
#include <common.h>
#include <ram.h>
#include <ppu.h>
#include <dma.h>
#include <cpu.h>

// Addresses Name Description
// 0000h – 3FFFh ROM0 Non-switchable ROM Bank.
// 4000h – 7FFFh ROMX Switchable ROM bank.
// 8000h – 9FFFh VRAM Video RAM, switchable (0-1) in GBC mode.
// A000h – BFFFh SRAM External RAM in cartridge, often battery buffered.
// C000h – CFFFh WRAM0 Work RAM.
// D000h – DFFFh WRAMX Work RAM, switchable (1-7) in GBC mode
// E000h – FDFFh ECHO Description of the behaviour below.
// FE00h – FE9Fh OAM (Object Attribute Table) Sprite information table.
// FEA0h – FEFFh UNUSED Description of the behaviour below.
// FF00h – FF7Fh I/O Registers I/O registers are mapped here.
// FF80h – FFFEh HRAM Internal CPU RAM
// FFFFh IE Register Interrupt enable flags.

u8 bus_read(u16 address){
    // printf("BUS READ ADDRES = %04X\n",address);
    if(address < 0x8000){// ROM BANK
        return cart_read(address);
    }
    else if(address < 0xA000){ // VRAM
        return ppu_vram_read(address);
    }
    else if(address < 0xC000){ //SRAM
        return cart_read(address);
    }
    else if(address < 0xE000){ // WRAM
        wram_read(address);
    }
    else if(address < 0xFE00){ // ECHORAM
        return 0;
    }
    else if(address < 0xFEA0){ // OAM
        if(dma_transfer()){
            return 0xFF;
        }
        return ppu_oam_read(address);
    }
    else if(address < 0xFF00){ // NOT USABLE
        return 0;
    }
    else if(address < 0xFF80){ // I/0 REGISTER
        return io_read(address);
    }
    else if(address == 0xFFFF){ // IE register
        return cpu_get_ie_reg();
    }
    return hram_read(address);
}

void bus_write(u16 address, u8 value){

    if(address < 0x8000){// ROM BANK
        cart_write(address,value);
    }
    else if(address < 0xA000){ // VRAM
        ppu_vram_write(address,value);
    }
    else if(address < 0xC000){ //SRAM
        NO_IMPLFROM("WRITE from bus.c SRAM");
    }
    else if(address < 0xE000){ // WRAM
        wram_write(address,value);
    }
    else if(address < 0xFE00){ // ECHORAM
    
    }
    else if(address < 0xFEA0){ // OAM
        if(dma_transfer()){
            return;
        }
        ppu_oam_write(address,value);
    }
    else if(address < 0xFF00){ // NOT USABLE
    }
    else if(address < 0xFF80){ // I/0 REGISTER
        io_write(address,value);
    }
    else if(address < 0xFFFF){ // HIGH RAM
        hram_write(address,value);
    }
    else if(address == 0xFFFF){ // IE register
        cpu_set_ie_reg(value);
    }
    else{
        NO_IMPL();
    }
}

u16 bus_read16(u16 address) {
    u16 lo = bus_read(address);
    u16 hi = bus_read(address + 1);

    return lo | (hi << 8);
}

void bus_write16(u16 address, u16 value) {
    bus_write(address + 1, (value >> 8) & 0xFF);
    bus_write(address, value & 0xFF);
}