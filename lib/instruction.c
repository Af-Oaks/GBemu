#include <instruction.h>

instruction instructions[0x100] = {
//  opcode    inst  |addres_m | mem1 | mem2 |  

    [0x00] = {IN_NOP, AM_IMP},

    [0x05] = {IN_DEC, AM_R, RT_B},

    [0x0E] = {IN_LD, AM_R_D8, RT_C},

    [0xAF] = {IN_XOR, AM_R, RT_A},

    [0xC3] = {IN_JP, AM_D16},

    [0xF3] = {IN_DI}
};


instruction *instruction_by_opcode(u8 opcode) {
    if(opcode > 0xFF || instructions[opcode].type == IN_NONE) {
        return NULL;
    }
    return &instructions[opcode];
}