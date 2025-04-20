#pragma once

#include <common.h>
#include <instruction.h>

typedef struct
{
    u8 a;
    u8 f;
    u8 b;
    u8 c;
    u8 d;
    u8 e;
    u8 h;
    u8 l;
    u16 sp;
    u16 pc;

} cpu_registers;

typedef struct
{
    cpu_registers regs;

    // context for the current operation in the cpu
    u16 fetch_data;
    u16 write_data;
    u16 mem_dest;
    bool dest_is_mem;
    u8 current_opcode;
    instruction *current_inst;

    //flagControls
    bool IME;
    bool enabling_ime;
    u8 ie_reg;
    u8 int_flags;

    // state of cpu
    bool halted;
    bool stepping;
} cpu_context;

static void fetch_instuction();
static void execute_instruction();
void cpu_init();
bool cpu_step();
void cpu_tick();

typedef void (*IN_PROC)(cpu_context*);
IN_PROC instruction_get_process(in_type type);

cpu_registers* cpu_get_regs();

u8 cpu_get_ie_reg();
void cpu_set_ie_reg(u8 value);
u8 cpu_get_int_flags();
void cpu_set_int_flags(u8 value);

u16 cpu_read_reg(reg_type rt);
void cpu_write_reg(reg_type rt, u16 val);

u8 cpu_read_reg_8(reg_type rt);
void cpu_write_reg_8(reg_type rt, u8 val);


#define CPU_FLAG_Z BIT(ctx->regs.f,7)
#define CPU_FLAG_N BIT(ctx->regs.f,6)
#define CPU_FLAG_H BIT(ctx->regs.f,5)
#define CPU_FLAG_C BIT(ctx->regs.f,4)