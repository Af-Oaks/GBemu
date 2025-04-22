#include <timer.h>
#include <interrupts.h>

static timer timer_ctx={0};

timer* timer_get_context() {
    return &timer_ctx;
}

void timer_init() {
    timer_ctx.DIV = 0xABCC;// why rocktriton used this value? docs said is ABCCh.....
    timer_ctx.TAC = 0b0000100;
}

void timer_tick() {
    u16 prev_div = timer_ctx.DIV;
    timer_ctx.DIV++;
    bool update_tima = false;
    if(timer_ctx.TAC == 4){// 4096hz mode -> every 1024
        if((prev_div & 0x3FFF )== 0){
            update_tima = true;
        }
    }
    else if(timer_ctx.TAC == 5){// 262144hz mode -> every 16
        if((prev_div & 0x000F) == 0){
            update_tima = true;
        }
    }
    else if(timer_ctx.TAC == 6){// 65536hz mode -> every 64
        if((prev_div & 0x003F) ==0){
            update_tima = true;
        }
    }
    else if(timer_ctx.TAC == 7){// 16386hz mode -> every 256
        if((prev_div & 0x00FF) ==0){
            update_tima = true;
        }
    }
    if(update_tima){ // proc overflow ? update tima?
        timer_ctx.TIMA++;
        if(timer_ctx.TIMA == 0xFF)// overflow
        {
            timer_ctx.TIMA = timer_ctx.TMA;//TODO: interrupts call!
            cpu_request_interrupt(IT_TIMER);
        }
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
        timer_ctx.TAC = value & 0b00001111;// only the first 3 bits is R/W
        return;
    }
    UNEXPECTED_ERROR("timer.c unexpected addres!");
}