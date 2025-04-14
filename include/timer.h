#pragma once

#include <common.h>


typedef struct 
{
    u8 TIMA;
    u8 TMA;
    u8 TAC;
    u16 DIV;
}timer;

void timer_init();
void timer_tick();

timer *timer_get_context();
u8 timer_read(u16 address);
void timer_write(u16 addres,u8 value);