#include <io.h>
#include <timer.h>
#include <cpu.h>
#include <lcd.h>

u8 ly=0;
static serial_data[2];

u8 io_read(u16 address){
    printf("bus_read(%04X)\n", address);
    if (address == 0xFF00) {
        return gamepad_read();
    }
    else if (address == 0xFF01){
        return serial_data[0];//serial data
    }
    else if (address == 0xFF02){
        return serial_data[1];
    }
    else if(address <=0xFF07){//TIMER AND DIVIDER
        printf("TIMER DIV READ\n");
        return timer_read(address);
    }
    else if(address == 0xFF0F){
        return cpu_get_int_flags();//interrups!
    }
    else if(address >= 0xFF10 && address <= 0xFF3F){
        return 0;//TODO sound
    }
    else if(address >= 0xFF40 && address <= 0xFF4B){
        return read_lcd_reg(address);//TODO LCD
    }
    // else if(address == 0xFF50){
    //     return;//TODO: boot rom
    // }
    // else if(address >= 0xFF50 || address <= 0xFF55){
    //     return;//TODO: VRAM DMA
    // }
    // else if(address >= 0xFF68 || address <= 0xFF6B){
    //     return;//TODO: BG /OBJ Pallets
    // }
    // else if(address == 0xFF70){
    //     return;//TODO: WRAM BANK SELECT
    // }
    NO_IMPLFROM("UNSUPPORTED IO_read\n");
}

void io_write(u16 address, u8 value){
    printf("bus_write(%04X)\n", address);
    if (address <= 0xFF00) {
        gamepad_set_sel(value);
        return;
    }
    else if (address == 0xFF01){
        return serial_data[0]=value;
    }
    else if (address == 0xFF02){
        return serial_data[1] = value;
    }
    else if(address>=0xFF04 && address <=0xFF07){//TIMER AND DIVIDER
        printf("TIMER DIV WRITE\n");
        return timer_write(address,value);
    }
    else if (address == 0xFF0F) {
        cpu_set_int_flags(value);//interrups!
        return;
    }
    else if(address >= 0xFF10 && address <= 0xFF3F){
        return;//TODO sound
    }
    else if(address >= 0xFF40 && address <= 0xFF4B){
        return write_lcd_reg(address,value);//TODO LCD
    }
    // else if(address == 0xFF50){
    //     return;//TODO: boot rom
    // }
    // else if(address >= 0xFF50 || address <= 0xFF55){
    //     return;//TODO: VRAM DMA
    // }
    // else if(address >= 0xFF68 || address <= 0xFF6B){
    //     return;//TODO: BG /OBJ Pallets
    // }
    // else if(address == 0xFF70){
    //     return;//TODO: WRAM BANK SELECT
    // }

    NO_IMPLFROM("UNSUPPORTED IO_write addres!\n");
}