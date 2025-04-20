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
    case AM_IMP:// no need to fetch data?
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
    case AM_R_A16: {
        u16 lo = bus_read(ctx.regs.pc);
        emu_cycles(1);

        u16 hi = bus_read(ctx.regs.pc + 1);
        emu_cycles(1);

        u16 addr = lo | (hi << 8);

        ctx.regs.pc += 2;
        ctx.fetch_data = bus_read(addr);
        emu_cycles(1);

        return;
    }

    case AM_MR_R:{
        ctx.fetch_data = cpu_read_reg(ctx.current_inst->reg_2);
        ctx.mem_dest = cpu_read_reg(ctx.current_inst->reg_1);
        ctx.dest_is_mem = true;
        if(ctx.current_inst->reg_1 == RT_C){
            ctx.mem_dest |= 0xFF00;
        }
        return;
    }
    
    case AM_MR_D8:{
        ctx.fetch_data = bus_read(ctx.regs.pc);
        emu_cycles(1);
        ctx.regs.pc++;
        ctx.mem_dest = cpu_read_reg(ctx.current_inst->reg_1);
        ctx.dest_is_mem = true;
    }

    case AM_R_MR:{
        u16 addres = cpu_read_reg(ctx.current_inst->reg_2);
        ctx.dest_is_mem = true;
        if(ctx.current_inst->reg_2 == RT_C){
            ctx.mem_dest |= 0xFF00;
        }
        ctx.fetch_data = bus_read(addres);

        return;
    }        
    case AM_MR:
    ctx.mem_dest = cpu_read_reg(ctx.current_inst->reg_1);
    ctx.dest_is_mem = true;
    ctx.fetch_data = bus_read(cpu_read_reg(ctx.current_inst->reg_1));
    emu_cycles(1);
    return;


    case AM_HLI_R:{
        ctx.fetch_data = cpu_read_reg(ctx.current_inst->reg_2);
        ctx.mem_dest = cpu_read_reg(ctx.current_inst->reg_1);
        ctx.dest_is_mem = true;
        cpu_write_reg(RT_HL, cpu_read_reg(RT_HL) + 1);//TODO: verify overflow to increase from reg H if need
        //verify if a need to change the mem_dest
        return;
    }
    case AM_R_HLI:{
        ctx.fetch_data = bus_read(cpu_read_reg(ctx.current_inst->reg_2));
        emu_cycles(1);
        cpu_write_reg(RT_HL, cpu_read_reg(RT_HL) + 1);//TODO: verify overflow to increase from reg H if need
        //verify if a need to change the mem_dest
        return;
    }

    case AM_HLD_R:{
        ctx.fetch_data = cpu_read_reg(ctx.current_inst->reg_2);
        ctx.mem_dest = cpu_read_reg(ctx.current_inst->reg_1);
        ctx.dest_is_mem = true;
        cpu_write_reg(RT_HL, cpu_read_reg(RT_HL) - 1);//TODO: verify underflow to decrease from reg H if need
        //verify if a need to change the mem_dest
        return;
    }

    case AM_A8_R:{
        ctx.fetch_data = cpu_read_reg(ctx.current_inst->reg_2);//why reg 2 ?
        ctx.mem_dest = bus_read(ctx.regs.pc) | 0xFF00;//This is right? 16 bit?
        ctx.dest_is_mem = true;
        ctx.regs.pc++;
        emu_cycles(1);
        return; 
    }

    case AM_D16_R:
    case AM_A16_R:{
        ctx.fetch_data = cpu_read_reg(ctx.current_inst->reg_2);
        u8 high = bus_read(ctx.regs.pc);
        u8 low = bus_read(ctx.regs.pc +1);
        ctx.mem_dest = (high<<8 )| low;
        ctx.dest_is_mem = true;
        ctx.regs.pc+=2;//read 2 8bits values
        emu_cycles(1);
        return; 
    }
    default:
        printf("Uknow address mode %d\n", ctx.current_inst->mode);
        UNEXPECTED_ERROR("fetch_data in cpu_fetche_data.c");
    }
}