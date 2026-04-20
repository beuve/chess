#ifndef TYPES_H
#define TYPES_H

#include <stdbool.h>
#include <stdint.h>

typedef int Zhash;
typedef uint64_t BB;

typedef enum Color { White, Black } Color;

// clang-format off
typedef enum Square: int {
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

typedef enum File: int { FA, FB, FC, FD, FE, FF, FG, FH } File;

typedef enum Rank: int { R1, R2, R3, R4, R5, R6, R7, R8 } Rank;

typedef enum BBFile : uint64_t {
  BB_FA = 0x0101010101010101,
  BB_FB = 0x0202020202020202,
  BB_FC = 0x0404040404040404,
  BB_FD = 0x0808080808080808,
  BB_FE = 0x1010101010101010,
  BB_FF = 0x2020202020202020,
  BB_FG = 0x4040404040404040,
  BB_FH = 0x8080808080808080,
} BBFile;

typedef enum BBRank : uint64_t {
  BB_R1 = 0x00000000000000FF,
  BB_R2 = 0x000000000000FF00,
  BB_R3 = 0x0000000000FF0000,
  BB_R4 = 0x00000000FF000000,
  BB_R5 = 0x000000FF00000000,
  BB_R6 = 0x0000FF0000000000,
  BB_R7 = 0x00FF000000000000,
  BB_R8 = 0xFF00000000000000
} BBRank;

// clang-format off
typedef enum BBSquare : uint64_t {
  BB_A1 = BB_FA & BB_R1, BB_B1 = BB_FB & BB_R1, BB_C1 = BB_FC & BB_R1, BB_D1 = BB_FD & BB_R1, 
  BB_E1 = BB_FE & BB_R1, BB_F1 = BB_FF & BB_R1, BB_G1 = BB_FG & BB_R1, BB_H1 = BB_FH & BB_R1,
  BB_A2 = BB_FA & BB_R2, BB_B2 = BB_FB & BB_R2, BB_C2 = BB_FC & BB_R2, BB_D2 = BB_FD & BB_R2, 
  BB_E2 = BB_FE & BB_R2, BB_F2 = BB_FF & BB_R2, BB_G2 = BB_FG & BB_R2, BB_H2 = BB_FH & BB_R2,
  BB_A3 = BB_FA & BB_R3, BB_B3 = BB_FB & BB_R3, BB_C3 = BB_FC & BB_R3, BB_D3 = BB_FD & BB_R3, 
  BB_E3 = BB_FE & BB_R3, BB_F3 = BB_FF & BB_R3, BB_G3 = BB_FG & BB_R3, BB_H3 = BB_FH & BB_R3,
  BB_A4 = BB_FA & BB_R4, BB_B4 = BB_FB & BB_R4, BB_C4 = BB_FC & BB_R4, BB_D4 = BB_FD & BB_R4, 
  BB_E4 = BB_FE & BB_R4, BB_F4 = BB_FF & BB_R4, BB_G4 = BB_FG & BB_R4, BB_H4 = BB_FH & BB_R4,
  BB_A5 = BB_FA & BB_R5, BB_B5 = BB_FB & BB_R5, BB_C5 = BB_FC & BB_R5, BB_D5 = BB_FD & BB_R5, 
  BB_E5 = BB_FE & BB_R5, BB_F5 = BB_FF & BB_R5, BB_G5 = BB_FG & BB_R5, BB_H5 = BB_FH & BB_R5,
  BB_A6 = BB_FA & BB_R6, BB_B6 = BB_FB & BB_R6, BB_C6 = BB_FC & BB_R6, BB_D6 = BB_FD & BB_R6, 
  BB_E6 = BB_FE & BB_R6, BB_F6 = BB_FF & BB_R6, BB_G6 = BB_FG & BB_R6, BB_H6 = BB_FH & BB_R6,
  BB_A7 = BB_FA & BB_R7, BB_B7 = BB_FB & BB_R7, BB_C7 = BB_FC & BB_R7, BB_D7 = BB_FD & BB_R7, 
  BB_E7 = BB_FE & BB_R7, BB_F7 = BB_FF & BB_R7, BB_G7 = BB_FG & BB_R7, BB_H7 = BB_FH & BB_R7,
  BB_A8 = BB_FA & BB_R8, BB_B8 = BB_FB & BB_R8, BB_C8 = BB_FC & BB_R8, BB_D8 = BB_FD & BB_R8, 
  BB_E8 = BB_FE & BB_R8, BB_F8 = BB_FF & BB_R8, BB_G8 = BB_FG & BB_R8, BB_H8 = BB_FH & BB_R8
} BBSquare;
// clang-format on

/**
 * Castling rights bitmask (heavily inspired by stockfish).
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

typedef enum Directions : int8_t {
  BottomLeft = -9,
  Bottom = -8,
  BottomRight = -7,
  Left = -1,
  Right = 1,
  TopLeft = 7,
  Top = 8,
  TopRight = 9,
} Directions;

#endif
