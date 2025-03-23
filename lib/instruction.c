#include <instruction.h>

instruction instructions[0x100] = {
//  opcode    inst  |addres_m | mem1 | mem2 |  

    [0x00] = {IN_NOP, AM_IMP},
    [0x05] = {IN_DEC, AM_R, RT_B},
    [0x0E] = {IN_LD, AM_R_D8, RT_C},
    //0x1X instructions
    [0x10] = {IN_STOP},
    [0x11] = {IN_LD, AM_R_D16,RT_DE},
    [0x14] = {IN_INC, AM_R, RT_D},
    [0x15] = {IN_DEC, AM_R, RT_D},
    //0x2X instructions
    [0x21] = {IN_LD, AM_R_D16, RT_HL},
    //0x3X instructions
    //0x4X instructions
    [0x47] = {IN_LD, AM_R_R ,RT_B, RT_A},
    //0x5X instructions
    //0x6X instructions
    //0x7X instructions
    //0x8X instructions
    //0x9X instructions
    //0xAX instructions
    [0xAF] = {IN_XOR, AM_R, RT_A},
    //0xBX instructions
    //0xCX instructions
    [0xC3] = {IN_JP, AM_D16},
    //0xDX instructions
    //0xEX instructions
    //0xFX instructions
    [0xF3] = {IN_DI}
};


instruction *instruction_by_opcode(u8 opcode) {
    printf("getting inst by opcode %x, type = %x\n",opcode,instructions[opcode].type);
    if(opcode > 0xFF || instructions[opcode].type == IN_NONE) {
        return NULL;
    }
    return &instructions[opcode];
}