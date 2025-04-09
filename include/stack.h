#pragma one

#include <common.h>
#include <cpu.h>
#include <bus.h>


void stk_push(u8 value);
void stk_push_16(u16 value);
u8 stk_pop();
u16 stk_pop_16();