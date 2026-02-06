#include "zobrist.h"
#include "position.h"
#include <stdlib.h>

void init_zobrist_numbers() {
  for (int i = 0; i < 793; i++) {
    Z_NUMBERS[i] = rand();
  }
}

const int TURN_OFFSET = 768;
const int CASTLING_OFFSET = 769;
const int EN_PASSANT_OFFSET = 785;

Zhash zhash_of_position(Position *position) {
  Zhash zhash = 0;
  for (Square sq = A1; sq <= H8; sq++) {
    Piece piece = position->board[sq];
    if (piece == NO_PIECE) continue;
    int z_index = (piece - 1) * sq;
    zhash ^= Z_NUMBERS[z_index];
  }
  zhash ^= Z_NUMBERS[TURN_OFFSET + position->turn];
  zhash ^= Z_NUMBERS[CASTLING_OFFSET + position->castling];
  zhash ^= Z_NUMBERS[EN_PASSANT_OFFSET + position->en_passant];
  return zhash;
}

Zhash zhash_of_piece_square(Piece p, Square sq) {
  // 0 ^ x = x, so this return will never change the zhash
  if (p == NO_PIECE) return 0;
  return Z_NUMBERS[(p - 1) * 64 + sq];
}
