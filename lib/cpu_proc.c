#include <cpu.h>
#include <emu.h>
#include <stack.h>
//process instructions
void cpu_set_flags(cpu_context *ctx, int8_t z, int8_t n, int8_t h, int8_t c) {
    if (z != -1) {
        if(z){
            ctx->regs.f |= (1<<7);
        }else{
            ctx->regs.f &= ~(1<<7);
        }
    }

    if (n != -1) {
        if(n){
            ctx->regs.f |= (1<<6);
        }else{
            ctx->regs.f &= ~(1<<6);
        }
    }

    if (h != -1) {
        if(h){
            ctx->regs.f |= (1<<5);
        }else{
            ctx->regs.f &= ~(1<<5);
        }
    }

    if (c != -1) {
        if(c){
            ctx->regs.f |= (1<<4);
        }else{
            ctx->regs.f &= ~(1<<4);
        }
    }
}

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
static bool is_16_bit(reg_type type){
    if(type >= RT_AF){
        return true;
    }
    return false;
}


static void proc_none(cpu_context *ctx){
    printf("invalid instruction\n");
    exit(-5);
}

static void proc_nop(cpu_context *ctx){
    printf("NOP instruction\n");
}

static void proc_jp(cpu_context *ctx){
    printf("PROC_JP INSTR\n");
    if(check_cond(ctx)){
        ctx->regs.pc = ctx->fetch_data;
        emu_cycles(1);
    }
}

static void proc_ld(cpu_context *ctx){
    printf("LD instruction!\n");
    if(ctx->dest_is_mem){
        if(is_16_bit(ctx->current_inst->reg_2)){
            emu_cycles(1);
            bus_write_16(ctx->mem_dest, ctx->fetch_data);
        }
        else{
            bus_write(ctx->mem_dest, ctx->fetch_data);
        }
        emu_cycles(1);
        return;
    }
    //default
    cpu_write_reg(ctx->current_inst->reg_1, ctx->fetch_data);
}

static void proc_inc(cpu_context *ctx){
    printf("INC INSTRUCTION NOT IMPL!\n");
}

static void proc_dec(cpu_context *ctx){
    printf("DEC INSTRUCTION NOT IMPL!\n");
}

static void proc_stop(cpu_context *ctx) {
    fprintf(stderr, "STOPPING!\n");
    exit(1);
}

static void goto_addr(cpu_context *ctx, u16 addr, bool pushpc) {
    printf("GOTO_ADDR INSTR\n");
    if (check_cond(ctx)) {
        ctx->regs.pc = addr;
        emu_cycles(1);
    }
}

static void proc_jr(cpu_context *ctx) {
    int8_t rel = (int8_t)(ctx->fetch_data & 0xFF);
    u16 addr = ctx->regs.pc + rel;
    goto_addr(ctx, addr, false);
    printf("JR INSTRUCIDIONT addrs = %04x , regs.pc = %04x !!!\n", addr,ctx->regs.pc);
}

static void proc_di(cpu_context *ctx) {
    ctx->IME = false;
    printf("DI INSTR , regs.pc = %04x !!!\n",ctx->regs.pc);
}

static void proc_sub(cpu_context *ctx){
    u8 result = ctx->regs.a - ctx->fetch_data;
    printf("SUB INST result: %02X = reg_A(%02X) - N8(%04X) ",result,ctx->regs.a,ctx->fetch_data);
    cpu_set_reg_8(RT_A,result);
    printf("after = %02X\n",ctx->regs.a);
}

static void proc_ldh(cpu_context *ctx){
    printf("LDH INSTR addr(%04X)!!\n",ctx->mem_dest | ctx->regs.a);
    if(ctx->current_inst->reg_1 == RT_A){
        cpu_set_reg_8(RT_A, bus_read(0xFF00 | ctx->fetch_data));
    }else{
        bus_write(ctx->mem_dest , ctx->regs.a);
    }
}

static void proc_rst(cpu_context *ctx){
    printf("RST INSTR PARAM = %04X \n!!",ctx->current_inst->param);
    goto_addr(ctx, ctx->current_inst->param, true);
}

static void proc_pop(cpu_context *ctx){
    printf("POP INSTR addr(%04X),!!\n",ctx->regs.sp);
    u16 low = stk_pop();
    emu_cycles(1);
    u16 hi = stk_pop();
    emu_cycles(1);
    u16 value = (hi<<8) | low;
    
    if(ctx->current_inst->reg_1 == RT_AF){
        cpu_write_reg(ctx->current_inst->reg_1,value & 0xFFF0);
    }else{
        cpu_write_reg(ctx->current_inst->reg_1,value);
    }
}

static void proc_push(cpu_context *ctx){
    printf("PUSH INSTR addr(%04X)!!\n",ctx->regs.sp);
    u16 low = cpu_read_reg(ctx->current_inst->reg_1) & 0xFF ;
    stk_push(low);
    emu_cycles(1);
    u16 hi = (cpu_read_reg(ctx->current_inst->reg_2) >>8 ) & 0xFF;
    stk_push(hi);
    emu_cycles(1);
}

static void proc_call(cpu_context *ctx){
    printf("CALL INSTR addr(%04X)!!\n",ctx->regs.sp);
    u16 addr = ctx->fetch_data;
    goto_addr(ctx, addr, true);
}

static void proc_daa(cpu_context * ctx){
    printf("CALL INSTR DAA NOT IMPL\n");
}

static void proc_ret(cpu_context *ctx){
    printf("CALL INSTR RET NOT IMPL\n");
}
static void proc_cp(cpu_context *ctx){
    printf("CALL INSTR CP NOT IMPL");
}

static void proc_and(cpu_context *ctx) {
    ctx->regs.a &= ctx->fetch_data;
    cpu_set_flags(ctx, ctx->regs.a == 0, 0, 1, 0);
}

static void proc_xor(cpu_context *ctx) {
    ctx->regs.a ^= ctx->fetch_data & 0xFF;
    cpu_set_flags(ctx, ctx->regs.a == 0, 0, 0, 0);
}

static void proc_or(cpu_context *ctx) {
    ctx->regs.a |= ctx->fetch_data & 0xFF;
    cpu_set_flags(ctx, ctx->regs.a == 0, 0, 0, 0);
}

static IN_PROC processors[] = {
    [IN_NONE] = proc_none,
    [IN_NOP] = proc_nop,
    [IN_JP] = proc_jp,
    [IN_JR] = proc_jr,
    [IN_LD] = proc_ld,
    [IN_INC] = proc_inc,
    [IN_DEC] = proc_dec,
    [IN_STOP] = proc_stop,
    [IN_DI] = proc_di,
    [IN_SUB] = proc_sub,
    [IN_LDH] = proc_ldh,
    [IN_POP] = proc_pop,
    [IN_PUSH] = proc_push,
    [IN_RST] = proc_rst,
    [IN_CALL] = proc_call,
    [IN_DAA] = proc_daa,
    [IN_RET] = proc_ret,
    [IN_CP] = proc_cp,
    [IN_OR] = proc_or,
    [IN_AND] = proc_and,
    [IN_XOR] = proc_xor
};

IN_PROC instruction_get_process(in_type type){
    return processors[type];
}