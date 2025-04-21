#pragma once

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

#define BIT(a, n) ((a & (1 << n)) ? 1 : 0)

#define BIT_SET(a, n, on) { if (on) a |= (1 << n); else a &= ~(1 << n);}

#define BETWEEN(a, b, c) ((a >= b) && (a <= c))

u32 get_ticks();
void delay(u32 ms);

#define NO_IMPL() { fprintf(stderr,"NOT IMPLEMENTED YET!\n"); exit(-5);}
#define NO_IMPLFROM(from) { fprintf(stderr,"NOT IMPLEMENTED YET = %s!\n",from); exit(-5);}

#define UNEXPECTED_ERROR(from) { fprintf(stderr,"UNEXPECTED_ERROR! from %s\n",from); exit(-5);}