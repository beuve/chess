#ifndef ATTACKS_H
#define ATTACKS_H

#include "bitboards.h"
#include "types.h"

BB _KING_MASKS[64];
BB _KNIGHT_MASKS[64];

BB bb_king_mask(Square);
BB bb_knight_mask(Square);
BB bb_queen_mask(Square, BB blockers);
BB bb_rook_mask(Square, BB blockers);
BB bb_bishop_mask(Square, BB blockers);

void init_masks(void) __attribute__((constructor));
void init_masks();

BB get_rook_attacks(Square, BB blockers);
BB get_bishop_attacks(Square, BB blockers);
BB get_queen_attacks(Square, BB blockers);
BB get_king_attacks(Square);
BB get_knight_attacks(Square);
BB get_pawns_attacks(BB pawns, Color);

bool is_square_attacked(Square, Bitboards, Color, BB blockers, Square captured_sq);
#endif
