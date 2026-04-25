#include "fen.h"
#include "move.h"
#include "piece.h"
#include "test.h"
#include "types.h"

int position1() {
  char *starting_fen = "rnbq1knr/pppp1ppp/8/b7/1R2R3/3P4/PPP2PPP/1NBQKBN1 w - - 0 1";
  Position p = position_of_fen(starting_fen);
  Zhash starting_zhash = p.zhash;

  Move m1 = {B4, D4, NormalMove, NO_PIECE_KIND};
  ASSERT(is_halfmove(m1, p), "rbd4 should not be a halfmouve");
  ASSERT(!is_legal(m1, p), "rbd4 should be illegal");

  Move m2 = {E4, D4, NormalMove, NO_PIECE_KIND};
  ASSERT(is_halfmove(m2, p), "red4 should be a halfmouve");
  ASSERT(is_legal(m2, p), "red4 should be legal");

  ReverseMoveInfos reverse_move_infos = make_move(m2, &p);
  char *position_fen = fen_of_position(&p);
  char *expected_fen = "rnbq1knr/pppp1ppp/8/b7/1R1R4/3P4/PPP2PPP/1NBQKBN1 b - "
                       "- 1 1";
  ASSERT_EQ_FEN(position_fen, expected_fen, "Mismatch between actual and expected FEN after red4");

  undo_move(m2, &p, reverse_move_infos);
  char *undo_fen = fen_of_position(&p);
  ASSERT_EQ_FEN(undo_fen, starting_fen, "Mismatch between actual and expected FEN after undo red4");
  ASSERT_EQ(starting_zhash, p.zhash, "Mismatch in undo zhash");
  return 0;
}

int position2() {
  char *starting_fen = "r1b1k2r/ppp1qppp/2np1n2/1Bb1p3/4P3/2NP1N2/PPP1QPPP/R3K1R1 w Qkq - 2 9";
  Position p = position_of_fen(starting_fen);
  Zhash starting_zhash = p.zhash;

  Move m1 = {E1, G1, CastlingMove, NO_PIECE_KIND};
  ASSERT(is_halfmove(m1, p), "O-O should be a halfmouve");
  // Castling here is illegal, but legality of castling is tested in movegen.
  
  Move m2 = {E1, C1, CastlingMove, NO_PIECE_KIND};
  ASSERT(is_halfmove(m2, p), "O-O-O should be a halfmouve");
  ASSERT(is_legal(m1, p), "O-O should be legal");

  ReverseMoveInfos reverse_move_infos = make_move(m2, &p);
  char *position_fen = fen_of_position(&p);
  char *expected_fen = "r1b1k2r/ppp1qppp/2np1n2/1Bb1p3/4P3/2NP1N2/PPP1QPPP/2KR2R1 b kq - 3 9";
  ASSERT_EQ_FEN(position_fen, expected_fen, "Mismatch between actual and expected FEN after O-O-O");

  undo_move(m2, &p, reverse_move_infos);
  char *undo_fen = fen_of_position(&p);
  ASSERT_EQ_FEN(undo_fen, starting_fen, "Mismatch between actual and expected FEN after undo red4");
  ASSERT_EQ(starting_zhash, p.zhash, "Mismatch in undo zhash");
  return 0;
}

int position3() {
  char *starting_fen = "rnb1kbnr/ppppq1pp/8/4PpP1/8/5N2/PPPP1P1P/RNBQKB1R w KQkq f6 0 2";
  Position p = position_of_fen(starting_fen);
  Zhash starting_zhash = p.zhash;

  Move m1 = {E5, F6, EnPassantMove, NO_PIECE_KIND};
  ASSERT(!is_halfmove(m1, p), "exf6 should not be a halfmouve");
  ASSERT(!is_legal(m1, p), "exf6 should be illegal");

  Move m2 = {G5, F6, EnPassantMove, NO_PIECE_KIND};
  ASSERT(!is_halfmove(m2, p), "gxf6 should not be a halfmouve");
  ASSERT(is_legal(m2, p), "gxf6 should be legal");

  ReverseMoveInfos reverse_move_infos = make_move(m2, &p);
  char *position_fen = fen_of_position(&p);
  char *expected_fen = "rnb1kbnr/ppppq1pp/5P2/4P3/8/5N2/PPPP1P1P/RNBQKB1R b KQkq - 0 2";
  ASSERT_EQ_FEN(position_fen, expected_fen, "Mismatch between actual and expected FEN after gxf6");

  undo_move(m2, &p, reverse_move_infos);
  char *undo_fen = fen_of_position(&p);
  ASSERT_EQ_FEN(undo_fen, starting_fen, "Mismatch between actual and expected FEN after undo red4");
  ASSERT_EQ(starting_zhash, p.zhash, "Mismatch in undo zhash");
  return 0;
}

int position4() {
  char *starting_fen = "q3kr2/1P5p/6p1/4Pp2/8/2P2K2/P6P/1R6 w - - 0 1";
  Position p = position_of_fen(starting_fen);
  Zhash starting_zhash = p.zhash;

  Move m1 = {B7, B8, PromotionMove, Queen};
  ASSERT(!is_halfmove(m1, p), "b8=Q+ should not be a halfmouve");
  ASSERT(!is_legal(m1, p), "b8=Q+ should be illegal");

  Move m2 = {B7, A8, PromotionMove, Knight};
  ASSERT(!is_halfmove(m2, p), "bxf6=N should not be a halfmouve");
  ASSERT(is_legal(m2, p), "bxf6=N should be legal");

  ReverseMoveInfos reverse_move_infos = make_move(m2, &p);
  char *position_fen = fen_of_position(&p);
  char *expected_fen = "N3kr2/7p/6p1/4Pp2/8/2P2K2/P6P/1R6 b - - 0 1";
  ASSERT_EQ_FEN(position_fen, expected_fen, "Mismatch between actual and expected FEN after bxf6=N");

  undo_move(m2, &p, reverse_move_infos);
  char *undo_fen = fen_of_position(&p);
  ASSERT_EQ_FEN(undo_fen, starting_fen, "Mismatch between actual and expected FEN after undo red4");
  ASSERT_EQ(starting_zhash, p.zhash, "Mismatch in undo zhash");
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
