#include "castling.h"
#include "piece.h"
#include "types.h"

bool can_castle(Position position, Color turn) {
  int mask = turn ? 0b1100 : 0b0011;
  return (position.castling & mask) > 0;
}

bool can_castle_king_side(Position position, Color turn) {
  int mask = turn ? 0b0100 : 0b0001;
  return (position.castling & mask) > 0;
}

bool can_castle_queen_side(Position position, Color turn) {
  int mask = turn ? 0b1000 : 0b0010;
  return (position.castling & mask) > 0;
}

CastlingRights castling_update_mask(Position *position, Move move) {
  if (position->turn == White) {
    if (position->board[move.from] == WKing) return ~WHITE_CASTLING;
    if (move.from == A1) return ~WHITE_K;
    if (move.from == H1) return ~WHITE_Q;
  }
  if (position->turn == Black) {
    if (position->board[move.from] == BKing) return ~BLACK_CASTLING;
    if (move.from == A8) return ~BLACK_K;
    if (move.from == H8) return ~BLACK_Q;
  }
  return ANY_CASTLING;
}
