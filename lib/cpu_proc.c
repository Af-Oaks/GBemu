#include <cpu.h>
#include <emu.h>
//process instructions

static bool check_cond(cpu_context *ctx){
    bool z = CPU_FLAG_Z;
    bool c = CPU_FLAG_C;

    switch(ctx->current_inst->cond){
        case CT_NONE : return true;
        case CT_NZ: return !z;
        case CT_Z: return z;
        case CT_NC: return !c;
        case CT_C: return c;
        default: return false;
    }
}


static void proc_none(cpu_context *ctx){
    printf("invalid instruction\n");
    exit(-5);
}

static void proc_nop(cpu_context *ctx){
    printf("NOP instruction\n");
}

static void proc_jp(cpu_context *ctx){
    if(check_cond(ctx)){
        ctx->regs.pc = ctx->fetch_data;
        emu_cycles(1);
    }
}

static void proc_ld(cpu_context *ctx){
    printf("LOAD INSTRUCTION!\n");
    //aq nesse carai
}

static void proc_inc(cpu_context *ctx){
    printf("INC INSTRUCTION!\n");
}

static void proc_dec(cpu_context *ctx){
    printf("DEC INSTRUCTION!\n");
}

static void proc_stop(cpu_context *ctx) {
    fprintf(stderr, "STOPPING!\n");
}

static IN_PROC processors[] = {
    [IN_NONE] = proc_none,
    [IN_NOP] = proc_nop,
    [IN_JP] = proc_jp,
    [IN_LD] = proc_ld,
    [IN_INC] = proc_inc,
    [IN_DEC] = proc_dec,
    [IN_STOP] = proc_stop,
};

IN_PROC instruction_get_process(in_type type){
    return processors[type];
}