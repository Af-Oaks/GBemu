#include <lcd.h>
#include <dma.h>

static lcd_context ctx;
static unsigned long colors_default[4] = {0xFFFFFFFF, 0xFFAAAAAA, 0xFF555555, 0xFF000000}; 

/*
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
*/

void lcd_init(){
    ctx.lcdc = 0b10010001;//lcd power on, BG & widown enabled, BG enabled
    ctx.stat = 0x00;
    ctx.scy = 0x00;
    ctx.scx = 0x00;
    ctx.ly = 0x00;
    ctx.lyc = 0x00;
    ctx.dma = 0x00;
    ctx.bgp = 0xFF;
    ctx.obp0 = 0xFF;
    ctx.obp1 = 0xFF;
    ctx.wy = 0x00;
    ctx.wx = 0x00;
}

lcd_context* get_lcd_context(){
    return &ctx;
}
bool is_ppu_lcd_on(){
    return ctx.lcdc & 0b10000000;
}

u8 read_lcd_reg(u16 address){
    
    if(0xFF40 == address){
        return ctx.lcdc;
    }
    else if(0xFF41 == address){
        return ctx.stat;
    }
    else if(0xFF42 == address){
        return ctx.scy;
    }
    else if(0xFF43 == address){
        return ctx.scx;
    }
    else if(0xFF44 == address){
        return ctx.ly;
    }
    else if(0xFF45 == address){
        return ctx.lyc;
    }
    else if(0xFF46 == address){
        return ctx.dma;
    }
    else if(0xFF47 == address){
        return ctx.bgp;
    }
    else if(0xFF48 == address){
        return ctx.obp0;
    }
    else if(0xFF49 == address){
        return ctx.obp1;
    }
    else if(0xFF4A == address){
        return ctx.wy;
    }
    else if(0xFF4B == address){
        return ctx.wx;
    }
    UNEXPECTED_ERROR("from read_lcd_reg");
}

void write_lcd_reg(u16 address,u8 value){
    
    if(0xFF40 == address){
        ctx.lcdc = value;
        return;
    }
    else if(0xFF41 == address){
        ctx.stat = value;
        return;
    }
    else if(0xFF42 == address){
        ctx.scy = value;
        return;
    }
    else if(0xFF43 == address){
        ctx.scx = value;
        return;
    }
    else if(0xFF44 == address){
        ctx.ly = value;
        return;
    }
    else if(0xFF45 == address){
        ctx.lyc = value;
        return;
    }
    else if(0xFF47 == address){
        ctx.bgp = value;
        return;
    }
    else if (address == 0xFF46) {
        ctx.dma = value;
        dma_start(value);
        printf("DMA START!\n");
        return;
    }
    else if(0xFF48 == address){
        ctx.obp0 = value;
        return;
    }
    else if(0xFF49 == address){
        ctx.obp1 = value;
        return;
    }
    else if(0xFF4A == address){
        ctx.wy = value;
        return;
    }
    else if(0xFF4B == address){
        ctx.wx = value;
        return;
    }
    printf("LCD WRITE %04X = %02X\n",address,value);
    UNEXPECTED_ERROR("from write_lcd_reg");
}