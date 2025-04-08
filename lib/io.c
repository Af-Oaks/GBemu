#include <io.h>
#include <timer.h>
#include <cpu.h>

u8 io_read(u16 address){
    printf("bus_read(%04X)\n", address);
    if (address == 0xFF00) {
        gamepad_read();
        return;
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
    if(address == 0xFF0F){
        return;//TODO interrups!
    }
    NO_IMPLFROM("UNSUPPORTED IO_write addres!\n");
}