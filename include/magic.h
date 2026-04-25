#ifndef MAGIC_H
#define MAGIC_H
#include "types.h"

typedef struct Magic {
    BB mask;
    BB magic;
    int shift;
    BB *attacks;
} Magic;

Magic _ROOK_MAGICS[64];
Magic _BISHOP_MAGICS[64];

void init_magics(void) __attribute__((constructor));
void init_magics();

#endif
