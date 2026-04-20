#ifndef ATTACKS_H
#define ATTACKS_H

#include "types.h"

BB get_rook_attacks(Square, BB blockers);
BB get_bishop_attacks(Square, BB blockers);
BB get_queen_attacks(Square, BB blockers);

BB get_king_attacks(Square);
BB get_knight_attacks(Square);

BB get_pawns_attacks(BB pawns, Color);

#endif
