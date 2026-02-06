#include "zobrist.h"
#include "position.h"
#include "types.h"
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
    zhash ^= zhash_of_piece_square(position->board[sq], sq);
  }
  zhash ^= position->turn ? color_zhash() : 0;
  zhash ^= zhash_of_castling_rights(position->castling);
  zhash ^= zhash_of_en_passant_square(position->en_passant);
  return zhash;
}

Zhash zhash_of_piece_square(Piece p, Square sq) {
  // 0 ^ x = x, so this return will never change the zhash
  if (p == NO_PIECE) return 0;
  return Z_NUMBERS[(p - 1) * 64 + sq];
}

Zhash zhash_of_castling_rights(CastlingRights rights) { return Z_NUMBERS[CASTLING_OFFSET + rights]; }

Zhash color_zhash() { return Z_NUMBERS[TURN_OFFSET]; }

Zhash zhash_of_en_passant_square(Square sq) {
  if (sq == NO_SQUARE) return 0;
  return Z_NUMBERS[EN_PASSANT_OFFSET + sq];
}
