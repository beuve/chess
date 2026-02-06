#ifndef CASTLING_H
#define CASTLING_H

#include "move.h"
#include "position.h"

bool can_castle(Position position, Color turn);
bool can_castle_king_side(Position position, Color turn);
bool can_castle_queen_side(Position position, Color turn);

/**
 * Returns a mask to set castling rights after a move.
 * Ones meaning no change should me made, zeros meaning
 * this move revoke casling rights.

 * For example, if the white king moves, we cancel all
 * castling rights for white, giving the mask 1100.
 */
CastlingRights castling_update_mask(Position *position, Move move);

#endif
