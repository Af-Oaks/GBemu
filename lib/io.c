#include <io.h>
#include <timer.h>
#include <cpu.h>

u8 io_read(u16 address){
    printf("bus_read(%04X)\n", address);
    if (address == 0xFF00) {
        gamepad_read();
        return;
    }
    else if(address <=0xFF07){//TIMER AND DIVIDER
        return;//TODO memory
    }
    else if(address == 0xFF0F){
        return;//TODO interrups!
    }
    else if(address >= 0xFF10 && address <= 0xFF3F){
        return;//TODO sound
    }
    else if(address >= 0xFF40 && address <= 0xFF4B){
        return;//TODO LCD
    }
    else if(address == 0xFF4C){
        return;//TODO LCD
    }
    else if(address == 0xFF50){
        return;//TODO: boot rom
    }
    else if(address >= 0xFF50 || address <= 0xFF55){
        return;//TODO: VRAM DMA
    }
    else if(address >= 0xFF68 || address <= 0xFF6B){
        return;//TODO: BG /OBJ Pallets
    }
    else if(address == 0xFF70){
        return;//TODO: WRAM BANK SELECT
    }
    NO_IMPLFROM("UNSUPPORTED IO_read\n");
}

void io_write(u16 address, u8 value){
    printf("bus_write(%04X)\n", address);
    if (address <= 0xFF00) {
        gamepad_set_sel(value);
        return;
    }
    else if(address <=0xFF07){//TIMER AND DIVIDER
        return;//TODO memory
    }
    else if(address == 0xFF0F){
        return;//TODO interrups!
    }
    else if(address >= 0xFF10 && address <= 0xFF3F){
        return;//TODO sound
    }
    else if(address >= 0xFF40 && address <= 0xFF4B){
        return;//TODO LCD
    }
    else if(address == 0xFF4C){
        return;//TODO LCD
    }
    else if(address == 0xFF50){
        return;//TODO: boot rom
    }
    else if(address >= 0xFF50 || address <= 0xFF55){
        return;//TODO: VRAM DMA
    }
    else if(address >= 0xFF68 || address <= 0xFF6B){
        return;//TODO: BG /OBJ Pallets
    }
    else if(address == 0xFF70){
        return;//TODO: WRAM BANK SELECT
    }

    NO_IMPLFROM("UNSUPPORTED IO_write addres!\n");
}