#include <cpu.h>
#include <bus.h>
#include <emu.h>

cpu_context ctx = {0};

void cpu_init() {
    ctx.regs.pc = 0x100;
    ctx.regs.sp = 0xFFFE;
    *((short *)&ctx.regs.a) = 0xB001;
    *((short *)&ctx.regs.b) = 0x1300;
    *((short *)&ctx.regs.d) = 0xD800;
    *((short *)&ctx.regs.h) = 0x4D01;
}

static void fetch_instuction(){
    ctx.current_opcode = bus_read(ctx.regs.pc++);
    ctx.current_inst = instruction_by_opcode(ctx.current_opcode);
    if(ctx.current_inst == NULL){
        printf("null opcode?\n");
        UNEXPECTED_ERROR("fetch_instruction() in cpu");
    }
}

void fetch_data();

static void execute_instruction(){
    IN_PROC proc = instruction_get_process(ctx.current_inst->type);
    if(proc == NULL){
        printf("null processor | instruction %d\n", ctx.current_inst->type);
        UNEXPECTED_ERROR("execute_instruction in cpu");
    }
    proc(&ctx);
}


bool cpu_step() {
    if(!ctx.halted){
        fetch_instuction();
        fetch_data();
        printf("ANTES - PC: %04X, OP: %02X, INST: %d\n", ctx.regs.pc, ctx.current_opcode, ctx.current_inst->type);
        execute_instruction();
        printf("DEPOIS - PC: %04X, OP: %02X, INST: %d\n", ctx.regs.pc, ctx.current_opcode, ctx.current_inst->type);
    }
    return true;
}