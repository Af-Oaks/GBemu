# GBemu
creating a gb emulator for studying purposes, 
using Gameboy Emulator Development from https://github.com/rockytriton/LLD_gbemu as a guide but not limited to.

-> my goal is to create a GB with minimal help possible to help me understand low level code and futher increase my abilities.

test comand in dir /build:
cd ..
cmake -S ..
make
cd GBemu
./gbemu ../../roms/01-special.gb

cd ..
cmake -S ..
make
cd GBemu
./gbemu ../../../Tetris.gb
