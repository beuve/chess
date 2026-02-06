#include "castling.h"

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
