#include <stdio.h>
#include <emu.h>
#include <cart.h>
#include <cpu.h>
#include <ui.h>
#include <dma.h>

#include <pthread.h>
#include <unistd.h>

/* 
  Emu components:

  |Cart|
  |CPU|
  |Address Bus|
  |PPU|
  |Timer|

*/


static emu_context ctx;

emu_context *emu_get_context() {
    return &ctx;
}

void *cpu_run(void *p){
    cpu_init();
    ctx.running = true;
    ctx.paused = false;
    ctx.close = false;
    ctx.ticks = 0;

    while(ctx.running){
        if(ctx.close){
            ui_close();
            ctx.running=false;
        }

        if (ctx.paused) {
            delay(10);
            continue;
        }

        if (!cpu_step()) {
            printf("CPU Stopped\n");
            return -3;
        }

        ctx.ticks++;
    }
}

int emu_run(int argc, char **argv) {
    if (argc < 2) {
        printf("Usage: emu <rom_file>\n");
        return -1;
    }

    if (!cart_load(argv[1])) {
        printf("Failed to load ROM file: %s\n", argv[1]);
        return -2;
    }

    printf("Cart loaded..\n");

    ui_init();
    
    pthread_t t1;

    if (pthread_create(&t1, NULL, cpu_run, NULL)) {
        fprintf(stderr, "FAILED TO START MAIN CPU THREAD!\n");
        return -1;
    }

    while(!ctx.close) {
        update_dbg_window();
        ui_handle_events();
    }

    return 0;
}

void emu_cycles(int cpu_cycles){
    for(int x=0;x<cpu_cycles;x++){
        for(int y=0;y<4;y++){
            ctx.ticks++;
            cpu_tick();
        }
        dma_tick();
    }
}