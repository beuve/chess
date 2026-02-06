#include "piece.h"
#include "position.h"
#include "test.h"
#include "types.h"

int pieces_conversions() {
  ASSERT_EQ(piece_kind_of_piece(WKing), King, "WKing is not a Queen");
  ASSERT_EQ(color_of_piece(WKing), White, "WKing is not white");
  ASSERT_EQ(piece_of_piece_kind_color(King, White), WKing,
            "King + White is not WKing");
  return 0;
}

int squares_conversion() {
  ASSERT_EQ(rank_of_square(F7), R7, "F7 is not Rank 7");
  ASSERT_EQ(file_of_square(D7), FD, "D3 is not File D");
  ASSERT_EQ(square_of_rk_fl(R8, FA), A8, "Rank 8 + File A is not A8");
  return 0;
}

int main() {
  int res = 0;
  res |= pieces_conversions();
  res |= squares_conversion();
  return res;
}
