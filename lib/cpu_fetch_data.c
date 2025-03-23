#include <cpu.h>
#include <bus.h>
#include <emu.h>

extern cpu_context ctx;

void fetch_data(){
    ctx.mem_dest = 0;
    ctx.dest_is_mem = false;

    if (ctx.current_inst == NULL){
        return;
    }

    switch (ctx.current_inst->mode){
    case AM_IMP:
        return;
    case AM_R:
        ctx.fetch_data = cpu_read_reg(ctx.current_inst->reg_1);
        return;
    case AM_R_R:
        ctx.fetch_data = cpu_read_reg(ctx.current_inst->reg_2);
        return;

    case AM_HL_SPR:
    case AM_R_A8:
    case AM_D8:
    case AM_R_D8:
        ctx.fetch_data = bus_read(ctx.regs.pc);
        emu_cycles(1);
        ctx.regs.pc++;
        return;

    case AM_D16:
    case AM_R_D16:{
        u16 lo = bus_read(ctx.regs.pc);
        emu_cycles(1);
        u16 hi = bus_read(ctx.regs.pc + 1);
        emu_cycles(1);
        ctx.fetch_data = (hi << 8) | lo;
        ctx.regs.pc += 2;
        return;
    }

    default:
        printf("Uknow address mode %d\n", ctx.current_inst->mode);
        UNEXPECTED_ERROR("fetch_data in cpu");
    }
}