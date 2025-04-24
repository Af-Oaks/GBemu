#include <ppu.h>
#include <lcd.h>




bool window_visible() {
    return LCDC_WIN_ENABLE && get_lcd_context()->wx >= 0 &&
    get_lcd_context()->wx <= 166 && get_lcd_context()->wy >= 0 &&
    get_lcd_context()->wy < YRES;
}