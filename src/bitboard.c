#include "bitboard.h"
#include "position.h"
#include "types.h"

BB bb_king_mask(Square sq) {
  BB mask = 0;

  int rk = rank_of_square(sq);
  int fl = file_of_square(sq);

  if (rk > R1) {
    mask |= 1ll << (sq + Bottom);
    if (fl > FA) mask |= 1ll << (sq + BottomLeft);
    if (fl < FH) mask |= 1ll << (sq + BottomRight);
  }

  if (fl > FA) mask |= 1ll << (sq + Left);
  if (fl < FH) mask |= 1ll << (sq + Right);

  if (rk < R8) {
    mask |= 1ll << (sq + Top);
    if (fl > FA) mask |= 1ll << (sq + TopLeft);
    if (fl < FH) mask |= 1ll << (sq + TopRight);
  }

  return mask;
}

BB bb_knight_mask(Square sq) {
  BB mask = 0;

  int rk = rank_of_square(sq);
  int fl = file_of_square(sq);

  if (fl > FA && rk > R2) mask |= 1ll << (sq + BottomLeft + Bottom);
  if (fl > FB && rk > R1) mask |= 1ll << (sq + BottomLeft + Left);
  if (fl < FG && rk < R8) mask |= 1ll << (sq + TopRight + Right);
  if (fl < FH && rk < R7) mask |= 1ll << (sq + TopRight + Top);
  if (fl < FG && rk > R1) mask |= 1ll << (sq + BottomRight + Right);
  if (fl < FH && rk > R2) mask |= 1ll << (sq + BottomRight + Bottom);
  if (fl > FA && rk < R7) mask |= 1ll << (sq + TopLeft + Top);
  if (fl > FB && rk < R8) mask |= 1ll << (sq + TopLeft + Left);

  return mask;
}

BB bb_queen_mask(Square sq, BB blockers) { return bb_rook_mask(sq, blockers) | bb_bishop_mask(sq, blockers); }

BB bb_rook_mask(Square sq, BB blockers) {
  BB mask = 0;

  int rk = rank_of_square(sq);
  int fl = file_of_square(sq);

  for (Rank _rk = rk + 1; _rk <= R8; _rk++) {
    BB sq_mask = 1ll << square_of_rk_fl(_rk, fl);
    mask |= sq_mask;
    if (sq_mask & blockers) break;
  }

  for (Rank _rk = rk - 1; _rk >= R1; _rk--) {
    BB sq_mask = 1ll << square_of_rk_fl(_rk, fl);
    mask |= sq_mask;
    if (sq_mask & blockers) break;
  }

  for (File _fl = fl - 1; _fl >= FA; _fl--) {
    BB sq_mask = 1ll << square_of_rk_fl(rk, _fl);
    mask |= sq_mask;
    if (sq_mask & blockers) break;
  }

  for (File _fl = fl + 1; _fl <= FH; _fl++) {
    BB sq_mask = 1ll << square_of_rk_fl(rk, _fl);
    mask |= sq_mask;
    if (sq_mask & blockers) break;
  }

  return mask;
}

BB bb_bishop_mask(Square sq, BB blockers) {
    BB mask = 0;
    Rank rk = rank_of_square(sq);
    File fl = file_of_square(sq);

    for (int i = 1; rk + i <= R8 && fl - i >= FA; ++i) {
        BB sq_mask = 1ULL << (sq + i * TopLeft);
        mask |= sq_mask;
        if (sq_mask & blockers) break;
    }

    for (int i = 1; rk + i <= R8 && fl + i <= FH; ++i) {
        BB sq_mask = 1ULL << (sq + i * TopRight);
        mask |= sq_mask;
        if (sq_mask & blockers) break;
    }

    for (int i = 1; rk - i >= R1 && fl - i >= FA; ++i) {
        BB sq_mask = 1ULL << (sq + i * BottomLeft);
        mask |= sq_mask;
        if (sq_mask & blockers) break;
    }

    for (int i = 1; rk - i >= R1 && fl + i <= FH; ++i) {
        BB sq_mask = 1ULL << (sq + i * BottomRight);
        mask |= sq_mask;
        if (sq_mask & blockers) break;
    }

    return mask;
}

