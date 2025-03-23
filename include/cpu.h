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

    // state of cpu
    bool halted;
    bool stepping;
} cpu_context;

static void fetch_instuction();
static void execute_instruction();
void cpu_init();
bool cpu_step();

typedef void (*IN_PROC)(cpu_context*);
IN_PROC instruction_get_process(in_type type);

#define CPU_FLAG_Z BIT(ctx->regs.f,7)
#define CPU_FLAG_N BIT(ctx->regs.f,6)
#define CPU_FLAG_H BIT(ctx->regs.f,5)
#define CPU_FLAG_C BIT(ctx->regs.f,4)