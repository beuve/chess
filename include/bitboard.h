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

BB _KING_MASKS[64];
BB _KNIGHT_MASKS[64];

BB bb_king_mask(Square sq);
BB bb_knight_mask(Square);
BB bb_queen_mask(Square sq, BB blockers);
BB bb_rook_mask(Square sq, BB blockers);
BB bb_bishop_mask(Square sq, BB blockers);

#endif
