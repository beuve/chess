#include "fen.h"
#include "move.h"
#include "piece.h"
#include "test.h"

int position1() {
  Position p = position_of_fen(
      "rnbq1knr/pppp1ppp/8/b7/1R2R3/3P4/PPP2PPP/1NBQKBN1 w - - 0 1");
  Move m1 = {E4, D4, NormalMove, NO_PIECE_KIND};
  ASSERT(is_halfmove(m1, p), "red4 should be a halfmouve");

  Move m2 = {B4, D4, NormalMove, NO_PIECE_KIND};
  ASSERT(is_halfmove(m2, p), "rbd4 should not be a halfmouve");
  return 0;
}

int position2() {
  Position p = position_of_fen(
      "r1b1k2r/ppp1qppp/2np1n2/1Bb1p3/4P3/2NP1N2/PPP1QPPP/R3K1R1 w Qkq - 2 9");
  Move m1 = {E1, G1, CastlingMove, NO_PIECE_KIND};
  ASSERT(!is_halfmove(m1, p), "O-O should not be a halfmouve");

  Move m2 = {E1, C1, CastlingMove, NO_PIECE_KIND};
  ASSERT(!is_halfmove(m2, p), "O-O-O should not be a halfmouve");
  return 0;
}

int position3() {
  Position p = position_of_fen(
      "rnb1kbnr/ppppq1pp/8/4PpP1/8/5N2/PPPP1P1P/RNBQKB1R w KQkq f6 0 2");
  Move m1 = {E5, F6, NormalMove, NO_PIECE_KIND};
  ASSERT(!is_halfmove(m1, p), "exf6 should not be a halfmouve");

  Move m2 = {G5, F6, NormalMove, NO_PIECE_KIND};
  ASSERT(!is_halfmove(m2, p), "gxf6 should not be a halfmouve");
  return 0;
}

int position4() {
  Position p = position_of_fen("q3kr2/1P5p/6p1/4Pp2/8/2P2K2/P6P/1R6 w - - 0 1");
  Move m1 = {B7, A8, PromotionMove, Knight};
  ASSERT(!is_halfmove(m1, p), "exf6 should not be a halfmouve");

  Move m2 = {B7, B8, PromotionMove, Queen};
  ASSERT(!is_halfmove(m2, p), "gxf6 should not be a halfmouve");
  return 0;
}

int main() {
  int res = 0;
  res |= position1();
  res |= position2();
  res |= position3();
  res |= position4();
  return res;
}
