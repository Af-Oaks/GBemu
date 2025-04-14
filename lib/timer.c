#include <timer.h>

static timer timer_ctx={0};

timer *timer_get_context() {
    return &timer_ctx;
}

void timer_init() {
    timer_ctx.DIV = 0xAC00;// why rocktriton used this value? docs said is ABCCh.....
}

void timer_tick() {
    //TODO: i dont know how to calculate the ticks
    u16 prev_div = timer_ctx.DIV;
    timer_ctx.DIV++;

    if(timer_ctx.TAC == 4){// 4096hz mode

    }
    else if(timer_ctx.TAC == 5){// 262144hz mode

    }
    else if(timer_ctx.TAC == 6){// 65536hz mode

    }
    else if(timer_ctx.TAC == 7){// 16386hz mode

    }

    if(timer_ctx.DIV == 0){ // proc overflow ?

    }

}

u8 timer_read(u16 address){
    if(address == 0xFF04){
        u8 value = timer_ctx.DIV >>8;
        return value;
    }
    else if(address == 0xFF05){
        return timer_ctx.TIMA;

    }
    else if(address == 0xFF06){
        return timer_ctx.TMA;
    }
    else if(address == 0xFF07){
        return timer_ctx.TAC;
    }
    UNEXPECTED_ERROR("timer.c unexpected addres!");
}
void timer_write(u16 address,u8 value){
    if(address == 0xFF04){
        timer_ctx.DIV = 0x0000;
        return;
    }
    else if(address == 0xFF05){
        timer_ctx.TIMA = value;
        return;
    }
    else if(address == 0xFF06){
        timer_ctx.TMA = value;
        return;
    }
    else if(address == 0xFF07){
        timer_ctx.TAC = value & 0b00000111;// only the first 3 bits is R/W
        return;
    }
    UNEXPECTED_ERROR("timer.c unexpected addres!");
}