#ifndef PRETTY_PRINT_H
#define PRETTY_PRINT_H

#include "piece.h"
#include "position.h"

const char *pretty_char_of_piece(Piece);
void char_of_square(Square sq, char *buffer);
void print_position(Position *);
void print_bitboard(BB);

#endif
