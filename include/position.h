#include "bitboard.h"
#include "piece.h"
#include <stdint.h>
#include <string.h>
#include <stdbool.h>

// clang-format off
typedef enum Square {
  A8, B8, C8, D8, E8, F8, G8, H8,
  A7, B7, C7, D7, E7, F7, G7, H7,
  A6, B6, C6, D6, E6, F6, G6, H6,
  A5, B5, C5, D5, E5, F5, G5, H5,
  A4, B4, C4, D4, E4, F4, G4, H4,
  A3, B3, C3, D3, E3, F3, G3, H3,
  A2, B2, C2, D2, E2, F2, G2, H2,
  A1, B1, C1, D1, E1, F1, G1, H1,
  NO_SQUARE
} Square;
// clang-format on

typedef struct Position {
  /** Bitboards for each piece type and/or color */
  Bitboards bitboards;

  /** Mailbox board representation (one piece per square, A8 = 0 .. H1 = 63) */
  Piece board[64];

  /**
   * Castling rights bitmask.
   *
   * The 4 least-significant bits encode castling availability:
   * - bit 0 (0001): White king-side  (K)
   * - bit 1 (0010): White queen-side (Q)
   * - bit 2 (0100): Black king-side  (k)
   * - bit 3 (1000): Black queen-side (q)
   */
  uint8_t castling;

  /** En-passant target square, or NO_SQUARE if none */
  Square en_passant;

  /** Full-move number */
  uint8_t num_moves;

  /** Half-move number for the 50-move rule */
  uint8_t num_halfmoves;

  /** Side to move:
   * - true: Black
   * - false: White
   */
  bool turn;
} Position;

void print_position(Position position);

Position position_of_fen(char *fen);
char *fen_of_position(Position *position);
