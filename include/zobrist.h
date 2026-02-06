#ifndef ZOBRIST_H
#define ZOBRIST_H

#include "piece.h"
#include "types.h"

struct Position;

Zhash Z_NUMBERS[793];

void init_zobrist_numbers(void) __attribute__((constructor));
void init_zobrist_numbers();

Zhash zhash_of_position(struct Position *p);
Zhash zhash_of_piece_square(Piece p, Square sq);
Zhash color_zhash();
Zhash zhash_of_castling_rights(CastlingRights rights);
Zhash zhash_of_en_passant_square(Square sq);
#endif
