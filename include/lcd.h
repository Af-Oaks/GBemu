#pragma once

#include <common.h>


typedef struct 
{
    u8 lcdc;// 0xFF40
    u8 stat;// 0xFF41
    u8 scy;// 0xFF42
    u8 scx;// 0xFF43
    u8 ly;//   0xFF44
    u8 lyc;//  0xFF45
    u8 dma;//  0xFF46
    u8 bgp;//  0xFF47
    u8 obp0;// 0xFF48
    u8 obp1;// 0xFF49
    u8 wy;//   0xFF4A
    u8 wx;//   0xFF4B
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
void lcd_init();
bool is_ppu_lcd_on();
