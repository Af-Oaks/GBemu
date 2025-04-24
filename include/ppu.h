#pragma once

#include <common.h>

static const int LINES_PER_FRAME = 154;
static const int TICKS_PER_LINE = 456;
static const int YRES = 144;
static const int XRES = 160;

typedef struct 
{
    u8 y;    //
    u8 x;    //
    u8 tile; //
    u8 f_cgb_pn : 3;
    u8 f_cgb_vram_bank : 1;
    u8 f_pn : 1;
    u8 f_x_flip : 1;
    u8 f_y_flip : 1;
    u8 f_bgp : 1;
}oam_entry;

typedef enum 
{
   FS_GET_TILE,
   FS_GET_TILE_LOW,
   FS_GET_TILE_HIGH,
   SLEEP,
   FS_PUSH
} FETCHER_STATE;

typedef struct 
{
    u8 color;
    u8 pallet;
    u8 sp_priority;
    u8 bg_priority;
}fifo_pixel;


typedef struct _fifo_entry
{
    struct _fifo_entry * next;
    fifo_pixel fifo_pixel;
}fifo_entry;

typedef struct 
{
    fifo_entry *back;
    fifo_entry *front;
    u32 size;
}fifo;

typedef struct 
{
    fifo_pixel fifo_pixel;
    oam_entry oam_entry;
    FETCHER_STATE fs_state;// one is enough?
    u8 line_x;
    u8 fetch_x;//hm....
    u8 push_x;
    u8 line_y;
    u8 fifo_number;
    


}pixel_context;



typedef struct 
{
    oam_entry oam_ram[0x40];
    u8 vram[0x2000];
}ppu_context;



void ppu_init();
void ppu_tick();
void ppu_render();
void ppu_vram_write(u16 address, u8 value);
u8 ppu_vram_read(u16 address);
void ppu_oam_write(u16 address, u8 value);
u8 ppu_oam_read(u16 address);