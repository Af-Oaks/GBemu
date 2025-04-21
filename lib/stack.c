#include <stack.h>

void stk_push(u8 value){
    cpu_get_regs()->sp--;
    bus_write(cpu_get_regs()->sp,value);
}
void stk_push_16(u16 value){
    u8 hi = (value >> 8 ) & 0xFF;
    u8 low = value & 0xFF;
    stk_push(hi);
    stk_push(low);
}

u8 stk_pop(){
    u16 val = cpu_get_regs()->sp++;
    return bus_read(val);
}

u16 stk_pop_16(){
    u16 low = stk_pop();
    u16 hi = stk_pop();
    return (hi << 8 ) | low;
}