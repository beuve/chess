#include "magic.h"
#include "bitboard.h"
#include "piece.h"
#include "types.h"
#include <stdlib.h>

int popcount(BB x) {
  x = x - ((x >> 1) & 0x5555555555555555ULL);
  x = (x & 0x3333333333333333ULL) + ((x >> 2) & 0x3333333333333333ULL);
  x = (x + (x >> 4)) & 0x0F0F0F0F0F0F0F0FULL;
  return (x * 0x0101010101010101ULL) >> 56;
}

BB get_piece_mask(Square sq, PieceKind pk, BB blockers) {
  if (pk == Rook) {
    return bb_rook_mask(sq, blockers);
  }
  return bb_bishop_mask(sq, blockers);
}

Magic get_square_magic(Square sq, PieceKind pk, pcg_t *rng) {
  BB blockers[4096] = {0};
  unsigned int epochs[4096] = {0};
  BB expected[4096] = {0};

  BB edges = ((BB_R1 | BB_R8) & ~(BB_R1 << ((sq / 8) * 8))) | ((BB_FA | BB_FH) & ~(BB_FA << (sq % 8)));
  BB mask = get_piece_mask(sq, pk, 0ll) & ~edges;

  BB n = 0;
  int size = 0;
  // Carry-Rippler trick
  do {
    blockers[size] = n;
    expected[size] = get_piece_mask(sq, pk, n);
    n = (n - mask) & mask;
    size++;
  } while (n);

  BB magic = 0ll;
  int shift = 64 - popcount(mask);
  BB *attacks = malloc(sizeof(BB) * size);
  unsigned int epoch = 0;
  bool failed = true;

  while (failed) {
    magic = rand_64(rng) & rand_64(rng) & rand_64(rng);
    failed = false;
    if (popcount((magic * mask) >> 56) > 6) continue;
    
    epoch++;
    for (int i = 0; i < size; i++) {
      int index = (magic * (blockers[i] & mask)) >> shift;
      if (epochs[index] < epoch) {
        epochs[index] = epoch;
        attacks[index] = expected[i];
      } else if (attacks[index] != expected[i]) {
        failed = true;
        break;
      }
    }
  }

  return (Magic){mask, magic, shift, attacks};
}

void init_magics() {
  pcg_t rng;
  pcg32_srandom_r(&rng, 0x12345678ULL, 0x9ABCDEFULL);
  for (Square sq = A1; sq <= H8; sq++) {
    _ROOK_MAGICS[sq] = get_square_magic(sq, Rook, &rng);
    _BISHOP_MAGICS[sq] = get_square_magic(sq, Bishop, &rng);
  }
}
