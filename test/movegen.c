#include "movegen.h"
#include "fen.h"
#include "position.h"
#include "test.h"
#include <stdio.h>
#include <stdlib.h>

bool contains(Square sq, Square *refs, int num_refs) {
  for (int i = 0; i < num_refs; i++) {
    if (sq == refs[i]) return true;
  }
  return false;
}

int test_king_movegen() {
  char *starting_fen = "r1bq3r/ppp2kpp/n4n2/2bpP3/Q4B2/2p2N2/PP1N1PPP/R3K1R1 w Q d6 0 12";
  Position p = position_of_fen(starting_fen);
  MoveList moves = list_king_moves(p);
  ASSERT_EQ(moves.size, 4, "There should be 4 possible moves for the King");
  Square expected_squares[4] = {C1, D1, F1, E2};
  while (moves.size > 0) {
    ASSERT(contains(ml_pop(&moves).to, expected_squares, 4), "Wrong move for King");
  }
  return 0;
}

int test_rook_movegen() {
  char *starting_fen = "r1bq3r/ppp2k1p/6p1/2npP2n/1R3B2/2p2N2/P2N1PPP/4K1R1 w - - 0 17";
  Position p = position_of_fen(starting_fen);
  MoveList moves = list_rooks_moves(p);
  ASSERT_EQ(moves.size, 12, "There should be 11 possible moves for the Rooks");
  Square expected_squares[12] = {B1, B2, B3, B5, B6, B7, C4, D4, E4, F1, H1, A4};
  while (moves.size > 0) {
    ASSERT(contains(ml_pop(&moves).to, expected_squares, 12), "Wrong move for Rook");
  }
  return 0;
}

int test_bishop_movegen() {
  char *starting_fen = "r1bq3r/ppp2k1p/n5p1/Q1bpP3/1R3Bn1/2p2N2/P2N1PPP/4K1R1 w - - 2 16";
  Position p = position_of_fen(starting_fen);
  MoveList moves = list_bishops_moves(p);
  ASSERT_EQ(moves.size, 6, "There should be 6 possible moves for the Bishops");
  Square expected_squares[11] = {E3, G3, G5, H6, B6, C7};
  while (moves.size > 0) {
    ASSERT(contains(ml_pop(&moves).to, expected_squares, 6), "Wrong move for Bishop");
  }
  return 0;
}

int test_knights_movegen() {
  char *starting_fen = "r1bq3r/ppp2k1p/n5p1/Q1bpP3/1R1N1Bn1/2p5/P2N1PPP/4K1R1 b - - 3 16";
  Position p = position_of_fen(starting_fen);
  MoveList moves = list_knights_moves(p);
  ASSERT_EQ(moves.size, 8, "There should be 8 possible moves for the Knights");
  Square expected_squares[8] = {F2, H2, E3, E5, F6, H6, B4, B8};
  while (moves.size > 0) {
    ASSERT(contains(ml_pop(&moves).to, expected_squares, 8), "Wrong move for Knight");
  }
  return 0;
}

int test_pawns_movegen() {
  char *starting_fen = "1k2pp2/3P1P2/8/8/3p4/8/2PP4/2K5 w - - 0 1";
  Position p = position_of_fen(starting_fen);
  MoveList moves = list_pawns_moves(p);
  ASSERT_EQ(moves.size, 15, "There should be 15 possible moves for the Pawns");
  Square expected_squares[5] = {C3, C4, D3, D8, E8};
  while (moves.size > 0) {
    ASSERT(contains(ml_pop(&moves).to, expected_squares, 5), "Wrong move for Pawns");
  }
  return 0;
}


int main() {
  int res = 0;
  res |= test_king_movegen();
  res |= test_rook_movegen();
  res |= test_bishop_movegen();
  res |= test_knights_movegen();
  res |= test_pawns_movegen();
  return res;
}
