#include <stdio.h>
#include <emu.h>
#include <cart.h>
#include <cpu.h>
#include <ui.h>

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

    cpu_init();
    
    ctx.running = true;
    ctx.paused = false;
    ctx.close = false;
    ctx.ticks = 0;

    while(ctx.running) {
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

        while(ctx.ticks ==10){
            update_dbg_window();
            ui_handle_events();
            if(ctx.close){
                ctx.ticks++;
            }
        }

        ctx.ticks++;
    }

    return 0;
}

void emu_cycles(int cpu_cycles){
    //TODO
}