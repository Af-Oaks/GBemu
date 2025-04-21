#include <cpu.h>
#include <bus.h>
#include <emu.h>
#include <interrupts.h>

cpu_context ctx = {0};

void cpu_init() {
    ctx.regs.pc = 0x100;
    ctx.regs.sp = 0xFFFE;
    *((short *)&ctx.regs.a) = 0xB001;
    *((short *)&ctx.regs.b) = 0x1300;
    *((short *)&ctx.regs.d) = 0xD800;
    *((short *)&ctx.regs.h) = 0x4D01;
    ctx.ie_reg =0;
    ctx.IME =false;
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
        u16 pc = ctx.regs.pc;
        fetch_instuction();
        fetch_data();
        char flags[16];
        sprintf(flags, "%c%c%c%c", 
            ctx.regs.f & (1 << 7) ? 'Z' : '-',
            ctx.regs.f & (1 << 6) ? 'N' : '-',
            ctx.regs.f & (1 << 5) ? 'H' : '-',
            ctx.regs.f & (1 << 4) ? 'C' : '-'
        );
        char inst[16];
        inst_to_str(&ctx, inst);

        printf("%08lX - %04X: %-12s (%02X %02X %02X) A: %02X F: %s BC: %02X%02X DE: %02X%02X HL: %02X%02X\n", 
            emu_get_context()->ticks,
            pc, inst, ctx.current_opcode,
            bus_read(pc + 1), bus_read(pc + 2), ctx.regs.a, flags, ctx.regs.b, ctx.regs.c,
            ctx.regs.d, ctx.regs.e, ctx.regs.h, ctx.regs.l);

        if (ctx.current_inst == NULL) {
            printf("Unknown Instruction! %02X\n", ctx.current_opcode);
            exit(-7);
        }
        execute_instruction();
    }
    else {
        //is halted...
        emu_cycles(1);

        if (ctx.int_flags) {
            ctx.halted = false;
        }
    }

    if (ctx.IME) {
        cpu_handle_interrupts(&ctx);
        ctx.enabling_ime = false;
    }

    if (ctx.enabling_ime) {
        ctx.IME = true;
    }

    return true;
}

cpu_registers* cpu_get_regs(){
    return &ctx.regs;
}

u8 cpu_get_ie_reg(){
    return ctx.ie_reg;
}
void cpu_set_ie_reg(u8 value){
    ctx.ie_reg = value;
}

void cpu_tick(){

}