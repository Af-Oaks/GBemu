#pragma once

#include <gamepad.h>
#include <common.h>


typedef struct 
{   //bit 7 and 6 is always 1
    bool select_buttons;//bit 5
    bool select_dpad;//bit 4
    u8 down_or_start;//bit 3
    u8 up_or_select;//bit 2
    u8 left_or_b;//bit 1
    u8 right_or_a;//bit 0

}Gamepad;


void  gamepad_set_sel(u8 value);
u8 gamepad_read();
bool is_select_buttons();
bool is_select_dpad();