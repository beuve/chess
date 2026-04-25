#include "castling.h"
#include "attacks.h"
#include "bitboards.h"
#include "piece.h"
#include "types.h"

bool can_castle(Position position, Color turn) {
  int mask = turn ? 0b1100 : 0b0011;
  return (position.castling & mask) > 0;
}

bool any_occupied_square(Position pos, Square start, Square stop) {
  for (Square sq = start; sq <= stop; sq++) {
    if (bb_all_pieces(pos.bitboards) & (1ll << sq)) return true;
  }
  return false;
}

bool any_attacked_square(Position pos, Square start, Square stop) {
  BB bb_all = bb_all_pieces(pos.bitboards);
  for (Square sq = start; sq <= stop; sq++) {
    if (is_square_attacked(sq, pos.bitboards, !pos.turn, bb_all, NO_SQUARE)) return true;
  }
  return false;
}

bool can_castle_king_side(Position pos, Color turn) {
  int mask = turn == White ? 0b0001 : 0b0100;
  if ((pos.castling & mask) == 0) return false;

  Square king_sq = pos.kings[turn];
  bool any_obstacle = any_occupied_square(pos, king_sq + 1, king_sq + 2);
  bool any_attacked_sq = any_attacked_square(pos, king_sq, king_sq + 2);
  return !any_obstacle & !any_attacked_sq;
}

bool can_castle_queen_side(Position pos, Color turn) {
  int mask = turn == White ? 0b0010 : 0b1000;
  if ((pos.castling & mask) == 0) return false;

  Square king_sq = pos.kings[turn];
  bool any_obstacle = any_occupied_square(pos, king_sq - 3, king_sq - 1);
  bool any_attacked_sq = any_attacked_square(pos, king_sq - 2, king_sq);
  return ((pos.castling & mask) > 0) & !any_obstacle & !any_attacked_sq;
}

CastlingRights castling_update_mask(Position *position, Move move) {
  if (position->turn == White) {
    if (position->board[move.from] == WKing) return ~WHITE_CASTLING;
    if (move.from == A1) return ~WHITE_Q;
    if (move.from == H1) return ~WHITE_K;
    if (move.to == A8) return ~BLACK_Q;
    if (move.to == H8) return ~BLACK_K;
  }
  if (position->turn == Black) {
    if (position->board[move.from] == BKing) return ~BLACK_CASTLING;
    if (move.from == A8 || move.to == A8) return ~BLACK_Q;
    if (move.from == H8 || move.to == H8) return ~BLACK_K;
    if (move.to == A1) return ~WHITE_Q;
    if (move.to == H1) return ~WHITE_K;
  }
  return ANY_CASTLING;
}
