#ifndef CASTLING_H
#define CASTLING_H

#include "position.h"

bool can_castle(Position position, Color turn);
bool can_castle_king_side(Position position, Color turn);
bool can_castle_queen_side(Position position, Color turn);

#endif
