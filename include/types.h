#ifndef TYPES_H
#define TYPES_H

#include <stdbool.h>
#include <stdint.h>

typedef int Zhash;
typedef uint64_t BB;

typedef enum Color { White, Black } Color;

// clang-format off
typedef enum Square {
  A1,B1,C1,D1,E1,F1,G1,H1,
  A2,B2,C2,D2,E2,F2,G2,H2,
  A3,B3,C3,D3,E3,F3,G3,H3,
  A4,B4,C4,D4,E4,F4,G4,H4,
  A5,B5,C5,D5,E5,F5,G5,H5,
  A6,B6,C6,D6,E6,F6,G6,H6,
  A7,B7,C7,D7,E7,F7,G7,H7,
  A8,B8,C8,D8,E8,F8,G8,H8,
  NO_SQUARE
} Square;
// clang-format on

typedef enum File { FA, FB, FC, FD, FE, FF, FG, FH } File;

typedef enum Rank { R1, R2, R3, R4, R5, R6, R7, R8 } Rank;

/**
 * Castling rights bitmask.
 *
 * The 4 least-significant bits encode castling availability:
 * - bit 0 (0001): White king-side  (K)
 * - bit 1 (0010): White queen-side (Q)
 * - bit 2 (0100): Black king-side  (k)
 * - bit 3 (1000): Black queen-side (q)
 */
typedef enum CastlingRights : uint8_t {
  NO_CASTLING,
  WHITE_K = 0b0001,
  WHITE_Q = 0b0010,
  BLACK_K = 0b0100,
  BLACK_Q = 0b1000,

  KING_SIDE = WHITE_K | BLACK_K,
  QUEEN_SIDE = WHITE_Q | BLACK_Q,
  WHITE_CASTLING = WHITE_K | WHITE_Q,
  BLACK_CASTLING = BLACK_K | BLACK_Q,
  ANY_CASTLING = WHITE_CASTLING | BLACK_CASTLING,
} CastlingRights;

#endif
