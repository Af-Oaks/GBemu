#include <lcd.h>




lcd_context ctx = {0};

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
    else if(0xFF44 == address){
        return ctx.ly;
    }
    else if(0xFF45 == address){
        return ctx.lyc;
    }
    UNEXPECTED_ERROR("from read_lcd_reg");
}

void write_lcd_reg(u16 address,u8 value){
    
    if(0xFF40 == address){
        ctx.lcdc = value;
    }
    else if(0xFF41 == address){
        ctx.stat = value;
    }
    else if(0xFF44 == address){
        ctx.ly = value;
    }
    else if(0xFF45 == address){
        ctx.lyc = value;
    }
    UNEXPECTED_ERROR("from write_lcd_reg");
}