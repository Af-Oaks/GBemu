#include <gamepad.h>

static Gamepad gamepad;

static void gamepad_state(){
    u8 stategame = (
        gamepad.right_or_a |
        gamepad.left_or_b |
        gamepad.up_or_select |
        gamepad.down_or_start |
        ((u8)gamepad.select_buttons << 4) |
        ((u8)gamepad.select_dpad << 5 ));
    printf("u8 gamepdas state =(%02X) | %02X = %02X \n",stategame,0xC0,stategame | 0xC0);
}

void  gamepad_set_sel(u8 value){
    printf("gamepad_set_sel(%02X)\n", value);
    gamepad_state();
    gamepad.right_or_a =    (u8)(0x01) & value;//bit 0
    gamepad.left_or_b =     (u8)(0x01 << 1) & value;//bit 1
    gamepad.up_or_select =  (u8)(0x01 << 2) & value;//bit 2
    gamepad.down_or_start = (u8)(0x01 << 3) & value;//bit 3
    gamepad.select_buttons =(u8)(0x01 << 4) & value;//bit 4
    gamepad.select_dpad =   (u8)(0x01 << 5) & value;//bit 5
    gamepad_state();
}

bool is_select_buttons(){
    return gamepad.select_buttons;
}
    
bool is_select_dpad(){
    return gamepad.select_dpad;
}

u8 gamepad_read(){
    return (0xC0 |
        gamepad.right_or_a |
        gamepad.left_or_b |
        gamepad.up_or_select |
        gamepad.down_or_start |
        ((u8)gamepad.select_buttons << 4) |
        ((u8)gamepad.select_dpad << 5 )
    );
}