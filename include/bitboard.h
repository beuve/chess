#ifndef BITBOARD_H
#define BITBOARD_H

#include "types.h"

typedef struct Bitboards {
  BB whites;
  BB blacks;

  BB kings;
  BB kinghts;
  BB rooks;
  BB queens;
  BB bishops;
} Bitboards;

#endif
