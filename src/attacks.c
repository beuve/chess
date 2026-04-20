#include "attacks.h"
#include "bitboard.h"
#include "magic.h"
#include "types.h"

BB get_king_attacks(Square sq) { return _KING_MASKS[sq]; }

BB get_knight_attacks(Square sq) { return _KNIGHT_MASKS[sq]; }

BB get_bitboard_attacks(Magic mg, BB blockers) {
  int index = ((mg.magic * (blockers & mg.mask)) >> mg.shift);
  return mg.attacks[index];
}

BB get_rook_attacks(Square sq, BB blockers) {
  Magic mg = _ROOK_MAGICS[sq];
  return get_bitboard_attacks(mg, blockers);
}

BB get_bishop_attacks(Square sq, BB blockers) {
  Magic mg = _BISHOP_MAGICS[sq];
  return get_bitboard_attacks(mg, blockers);
}

BB get_queen_attacks(Square sq, BB blockers) {
  return get_bishop_attacks(sq, blockers) | get_rook_attacks(sq, blockers);
}

BB get_pawns_attacks(BB pawns, Color c) {
  if (c == White) {
    BB east = (pawns << 9) & !BB_FA;
    BB west = (pawns << 7) & !BB_FH;
    return east | west;
  } else {
    BB east = (pawns >> 7) & !BB_FA;
    BB west = (pawns >> 9) & !BB_FH;
    return east | west;
  }
}
