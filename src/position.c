#include "position.h"
#include "bitboards.h"
#include "piece.h"
#include "types.h"
#include "zobrist.h"
#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>

Square pawn_push(Square sq, Color c) {
  if (c) {
    return sq + Bottom;
  }
  return sq + Top;
}

Square pawn_is_origin_square(Square sq, Color c) {
  if (c) {
    return rank_of_square(sq) == R7;
  }
  return rank_of_square(sq) == R2;
}

Piece remove_piece(Position *position, Square from) {
  position->zhash ^= zhash_of_piece_square(position->board[from], from);
  Piece removed_piece = position->board[from];
  position->board[from] = NO_PIECE;
  bb_switch_piece(&position->bitboards, removed_piece, from);
  return removed_piece;
}

Piece put_piece(Position *position, Square to, Piece piece) {
  Piece removed_piece = position->board[to];
  if (position->board[to] != NO_PIECE) remove_piece(position, to);
  position->zhash ^= zhash_of_piece_square(piece, to);
  position->board[to] = piece;
  bb_switch_piece(&position->bitboards, piece, to);
  return removed_piece;
}

Piece move_piece(Position *position, Square from, Square to) {
  Piece moved_piece = remove_piece(position, from);
  PieceKind moved_piece_kind = piece_kind_of_piece(moved_piece);
  if (moved_piece_kind == King) {
    Color moved_piece_color = color_of_piece(moved_piece);
    position->kings[moved_piece_color] = to;
  }
  return put_piece(position, to, moved_piece);
}

Piece promote_piece(Position *position, Square from, Square to, PieceKind piece_kind) {
  Color piece_color = color_of_piece(position->board[from]);
  Piece piece = make_piece(piece_kind, piece_color);

  Piece removed_piece = remove_piece(position, from);
  assert(piece_kind_of_piece(removed_piece) == Pawn);
  return put_piece(position, to, piece);
}

void unpromote_piece(Position *position, Square from, Square to) {
  Color piece_color = color_of_piece(position->board[from]);
  Piece piece = make_piece(Pawn, piece_color);
  remove_piece(position, from);
  put_piece(position, to, piece);
}

Square square_of_rk_fl(Rank rk, File fl) { return rk * 8 + fl; }

Rank rank_of_square(Square sq) { return sq / 8; }

File file_of_square(Square sq) { return sq % 8; }
