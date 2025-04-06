#include <io.h>
#include <timer.h>
#include <cpu.h>


u8 io_read(u16 address){

}

void io_write(u16 address, u8 value){
    printf("bus_write(%04X)\n", address);
    if (address == 0xFF00) {
        gamepad_set_sel(value);
        return;
    }
    
    NO_IMPLFROM("UNSUPPORTED bus_write\n");
}