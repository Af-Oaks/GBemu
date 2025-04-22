#include <stack.h>

void stk_push(u8 value){
    cpu_get_regs()->sp--;
    bus_write(cpu_get_regs()->sp,value);
}
void stk_push_16(u16 value){
    stk_push((value >> 8 ) & 0xFF);
    stk_push(value & 0xFF);
}

u8 stk_pop(){
    return bus_read(cpu_get_regs()->sp++);
}

u16 stk_pop_16(){
    u16 low = stk_pop();
    u16 hi = stk_pop();
    return (hi << 8 ) | low;
}