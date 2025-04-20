#include <dma.h>
#include <ppu.h>
#include <bus.h>

static dma_context ctx;

void dma_start(u8 value){
    ctx.active =true;
    ctx.byte = 0;
    ctx.value = value;
    ctx.delay = 2;
}

void dma_tick(){

    if(!ctx.active){
        return;
    }

    if(ctx.delay){
        ctx.delay--;
        return;
    }

    ppu_oam_write(ctx.byte , bus_read(ctx.value*100 +ctx.byte));

    ctx.byte++;
    ctx.active = ctx.byte < 0xA0;
    if(!ctx.active){
        printf("DMA DONE!\n");
        sleep(100);
    }
}

bool dma_transfer(){
    return ctx.active;
}