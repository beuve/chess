#include "fen.h"
#include "castling.h"
#include "piece.h"
#include "test.h"
#include "types.h"

int position1() {
  Position p = position_of_fen(
      "N1bk2r1/pp6/3p2q1/2b1p3/2B1P3/6nP/PPP2PPK/R3R3 b - - 1 18");

  ASSERT_EQ(p.turn, Black, "It should be white's turn");
  ASSERT_EQ(p.num_halfmoves, 1, "Half Moves should be 0");
  ASSERT_EQ(p.num_moves, 18, "Half Moves should be 18");
  ASSERT_EQ(p.en_passant, NO_SQUARE,
            "There should not be an en passant square");

  ASSERT_EQ(p.board[A1], WRook, "A1 should be WRook");
  ASSERT_EQ(p.board[D8], BKing, "D8 should be BKing");
  ASSERT_EQ(p.board[F5], NO_PIECE, "D8 should be Empty (NO_PIECE)");

  ASSERT(!can_castle(p, White), "White should not be able to castle");
  ASSERT(!can_castle(p, Black), "Black should not be able to castle");
  return 0;
}

int position2() {
  Position p = position_of_fen(
      "r1bq3r/ppp2kpp/2n2n2/2bpP3/8/2p2N2/PP3PPP/RNBQK1R1 w Q d6 0 9");

  ASSERT_EQ(p.turn, White, "It should be black's turn");
  ASSERT_EQ(p.num_halfmoves, 0, "Half Moves should be 0");
  ASSERT_EQ(p.num_moves, 9, "Half Moves should be 18");
  ASSERT_EQ(p.en_passant, D6,
            "White should be able to capture in D6 en passant");

  ASSERT_EQ(p.board[B7], BPawn, "B7 should be BPawn");
  ASSERT_EQ(p.board[F3], WKnight, "F3 should be WKnight");
  ASSERT_EQ(p.board[E8], NO_PIECE, "E8 should be Empty (NO_PIECE)");

  ASSERT(!can_castle(p, Black), "Black should not be able to castle");
  ASSERT(!can_castle_king_side(p, White),
         "White should not be able to castle king side");
  ASSERT(can_castle_queen_side(p, White),
         "White should be able to castle queen side");
  return 0;
}

int main() {
  int res = 0;
  res |= position1();
  res |= position2();
  return res;
}
