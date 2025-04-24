#include <ppu.h>
#include <lcd.h>

extern ppu_context ctx;


void ppu_mode0_hblank() {   //mode 0 horizontal blank can acess vram,oam
                            // Waiting until the end of the scanline

}

void ppu_mode1_vblank() {   //mode 1
                            //Waiting until the next frame

}

void ppu_mode2_oam() {  //mode 2 OAM scan can acess vramm
                        //Searching for OBJs which overlap this line

}


void ppu_mode3_draw() { //mode 3 Drawing pixel, no acess
                        //Sending pixels to the LCD

}

