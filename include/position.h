#ifndef POSITION_H
#define POSITION_H

#include "bitboard.h"
#include "piece.h"
#include "types.h"
#include "zobrist.h"
#include <stdint.h>
#include <string.h>

typedef struct Position {
  /** Bitboards for each piece type and/or color */
  Bitboards bitboards;

  /** Mailbox board representation (one piece per square, A1 = 0 .. H8 = 63) */
  Piece board[64];

  CastlingRights castling;

  /** En-passant target square, or NO_SQUARE if none */
  Square en_passant;

  /** Full-move number */
  uint8_t num_moves;

  /** Half-move number for the 50-move rule */
  uint8_t num_halfmoves;

  /** Side to move:
   * - 0: White
   * - 1: Black
   */
  Color turn;

  /** Zobrist hashing of the position */
  Zhash zhash;
} Position;

void print_position(Position *position);

Rank rank_of_square(Square sq);
File file_of_square(Square sq);
Square square_of_rk_fl(Rank rk, File fl);

/**
 * Move a piece from square [from] to square [to].
 * Update the representations: mailbox, bitboards and Zhash.
 *
 * If a piece is present in [to], the representations
 * are updated accordingly. Appart from that, no checks
 * are performed.
 */
Piece move_piece(Position *position, Square from, Square to);

/**
 * Remove a piece from square [from].
 * Update the mailbox, bitboards and Zhash.
 */
Piece remove_piece(Position *position, Square from);

/**
 * Put a piece on square [to].
 * Update the representations: mailbox, bitboards and Zhash.
 *
 * If a piece is present in [to], the representations
 * are updated accordingly. Appart from that, no checks
 * are performed.
 */
Piece put_piece(Position *position, Square to, Piece piece);

/**
 * Promote a piece by removing piece from [from] and adding
 * a piece of kind [piece_kind] to [to].
 * Update the representations: mailbox, bitboards and Zhash.
 *
 * If a piece is present in [to], the representations
 * are updated accordingly. Appart from that, no checks
 * are performed. Notably, no checks verify that the piece
 * in [from] is a Pawn.
 */
Piece promote_piece(Position *position, Square from, Square to,
                    PieceKind piece_kind);

#endif
