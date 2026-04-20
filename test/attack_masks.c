#include "bitboard.h"
#include "test.h"
#include "types.h"
#include <stdio.h>

int king_attacks() {
  BB expected_mask;

  expected_mask = BB_A1 | BB_B1 | BB_B2 | BB_B3 | BB_A3;
  ASSERT_EQ(bb_king_mask(A2), expected_mask, "Wrong King attacks for square A2");

  expected_mask = BB_G7 | BB_G8 | BB_H7;
  ASSERT_EQ(bb_king_mask(H8), expected_mask, "Wrong King attacks for square H8");

  expected_mask = BB_D4 | BB_E4 | BB_F4 | BB_D5 | BB_F5 | BB_D6 | BB_E6 | BB_F6;
  ASSERT_EQ(bb_king_mask(E5), expected_mask, "Wrong King attacks for square E5");
  return 0;
}

int knight_attacks() {
  BB expected_mask;
  
  expected_mask = BB_C1 | BB_C3 | BB_B4;
  ASSERT_EQ(bb_knight_mask(A2), expected_mask, "Wrong Knight attacks for square A2");

  expected_mask = BB_G6 | BB_F7;
  ASSERT_EQ(bb_knight_mask(H8), expected_mask, "Wrong Knight attacks for square H8");

  expected_mask = BB_D3 | BB_C4 | BB_C6 | BB_D7 | BB_F7 | BB_G6 | BB_G4 | BB_F3;
  ASSERT_EQ(bb_knight_mask(E5), expected_mask, "Wrong Knight attacks for square E5");
  return 0;
}

int rook_attacks() {
  BB blockers, expected_mask;
  
  blockers = BB_D6 | BB_B4 | BB_G7; 
  expected_mask = (BB_D1 | BB_D2 | BB_D3 | BB_D5 | BB_D6) |
                  (BB_B4 | BB_C4 | BB_E4 | BB_F4 | BB_G4 | BB_H4);
  ASSERT_EQ(bb_rook_mask(D4, blockers), expected_mask, "Rook D4 blocked at D6 and B4");

  blockers = BB_A2 | BB_B1;
  expected_mask = BB_A2 | BB_B1;
  ASSERT_EQ(bb_rook_mask(A1, blockers), expected_mask, "Rook A1 tightly blocked");

  return 0;
}

int bishop_attacks() {
  BB blockers, expected_mask;
  
  blockers = BB_C2 | BB_C6 | BB_G6 | BB_G2;
  expected_mask = (BB_D3 | BB_C2) | (BB_D5 | BB_C6) | 
                  (BB_F5 | BB_G6) | (BB_F3 | BB_G2);
  ASSERT_EQ(bb_bishop_mask(E4, blockers), expected_mask, "Bishop E4 blocked on all diagonals");

  blockers = BB_C3;
  expected_mask = BB_B2 | BB_C3;
  ASSERT_EQ(bb_bishop_mask(A1, blockers), expected_mask, "Bishop A1 blocked at C3");

  return 0;
}

int sliding_pieces() { return 0; }

int main() {
  int res = 0;
  res |= king_attacks();
  res |= knight_attacks();
  res |= bishop_attacks();
  res |= rook_attacks();
  return res;
}
