#pragma once

#include <common.h>


typedef struct 
{
    u8 lcdc;// 0xFF40
    u8 stat;// 0xFF41
    u8 ly;//   0xFF44
    u8 lyc;//  0xFF45
} lcd_context;

typedef enum {
    MODE_HBLANK,
    MODE_VBLANK,
    MODE_OAM,
    MODE_XFER
} lcd_mode;


lcd_context* get_lcd_context();
u8 read_lcd_reg(u16 address);
void write_lcd_reg(u16 address,u8 value);

bool is_ppu_lcd_on();
