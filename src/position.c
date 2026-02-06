#include "position.h"
#include "piece.h"
#include "types.h"
#include "zobrist.h"
#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>

void print_position(Position *position) {
  for (int rk = R8; rk >= R1; rk--) {
    printf("%d ", rk + 1);
    for (File fl = FA; fl <= FH; fl++) {
      Square sq = square_of_rk_fl(rk, fl);
      printf("%s ", pretty_char_of_piece(position->board[sq]));
    }
    printf("\n");
  }
  printf("  A B C D E F G H\n");
}

Piece move_piece(Position *position, Square from, Square to) {
  Piece moved_piece = remove_piece(position, from);
  return put_piece(position, to, moved_piece);
}

Piece remove_piece(Position *position, Square from) {
  position->zhash ^= zhash_of_piece_square(position->board[from], from);
  Piece removed_piece = position->board[from];
  position->board[from] = NoPiece;
  return removed_piece;
}

Piece put_piece(Position *position, Square to, Piece piece) {
  Piece removed_piece = position->board[to];
  if (position->board[to] != NoPiece) remove_piece(position, to);
  position->zhash ^= zhash_of_piece_square(piece, to);
  position->board[to] = piece;
  return removed_piece;
}

Piece promote_piece(Position *position, Square from, Square to,
                    PieceKind piece_kind) {
  Color piece_color = color_of_piece(position->board[from]);
  Piece piece = piece_of_piece_kind_color(piece_kind, piece_color);

  Piece removed_piece = remove_piece(position, from);
  assert(piece_kind_of_piece(removed_piece) == Pawn);
  return put_piece(position, to, piece);
}

Square square_of_rk_fl(Rank rk, File fl) { return rk * 8 + fl; }

Rank rank_of_square(Square sq) { return sq / 8; }

File file_of_square(Square sq) { return sq % 8; }
