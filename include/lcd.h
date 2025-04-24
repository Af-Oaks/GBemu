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

#define LCDC_BGW_ENABLE (BIT(get_lcd_context()->lcdc, 0))
#define LCDC_OBJ_ENABLE (BIT(get_lcd_context()->lcdc, 1))
#define LCDC_OBJ_HEIGHT (BIT(get_lcd_context()->lcdc, 2) ? 16 : 8)
#define LCDC_BG_MAP_AREA (BIT(get_lcd_context()->lcdc, 3) ? 0x9C00 : 0x9800)
#define LCDC_BGW_DATA_AREA (BIT(get_lcd_context()->lcdc, 4) ? 0x8000 : 0x8800)
#define LCDC_WIN_ENABLE (BIT(get_lcd_context()->lcdc, 5))
#define LCDC_WIN_MAP_AREA (BIT(get_lcd_context()->lcdc, 6) ? 0x9C00 : 0x9800)
#define LCDC_LCD_ENABLE (BIT(get_lcd_context()->lcdc, 7))

#define LCDS_MODE ((lcd_mode)(get_lcd_context()->stat & 0b11))
#define LCDS_MODE_SET(mode) { get_lcd_context()->stat &= ~0b11; get_lcd_context()->stat |= mode; }

#define LCDS_LYC (BIT(get_lcd_context()->stat, 2))
#define LCDS_LYC_SET(b) (BIT_SET(get_lcd_context()->stat, 2, b))


lcd_context* get_lcd_context();
u8 read_lcd_reg(u16 address);
void write_lcd_reg(u16 address,u8 value);
void lcd_init();
bool is_ppu_lcd_on();
