#include <cpu.h>
#include <bus.h>
#include <emu.h>

cpu_context ctx = {0};

void cpu_init() {

}

static void fetch_instuction(){
    ctx.current_opcode = bus_read(ctx.regs.pc++);
    ctx.current_inst = instruction_by_opcode(ctx.current_opcode);
    if(ctx.current_inst == NULL){
        printf("null opcode\n");
        UNEXPECTED_ERROR("fetch_instruction in cpu");
    }
}

static void fetch_data(){
    ctx.mem_dest =0;
    ctx.dest_is_mem = false;

    switch(ctx.current_inst->mode){
        case AM_NONE: UNEXPECTED_ERROR("fetch_data in cpu");
        case AM_IMP: return;
        case AM_R: 
            ctx.fetch_data = cpu_read_reg(ctx.current_inst->reg_1);
            return;
        case AM_R_D8:
            ctx.fetch_data = bus_read(ctx.regs.pc);
            emu_cycles(1);
            return;
        case AM_D16:{
            u16 lo = bus_read(ctx.regs.pc);
            emu_cycles(1);
            u16 hi = bus_read(ctx.regs.pc + 1);
            emu_cycles(1);
            ctx.fetch_data = (hi << 8) | lo;
            ctx.regs.pc += 2;
            return;
        }
        default: 
        printf("Uknow address mode %d\n",ctx.current_inst->mode);
        UNEXPECTED_ERROR("fetch_data in cpu");
    }
}

static void execute_instruction(){
    printf("Cpu not Execeuting YET.\n");
}


bool cpu_step() {
    if(!ctx.halted){
        fetch_instuction();
        fetch_data();
        execute_instruction();
    }
    return true;
}