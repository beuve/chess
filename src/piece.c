#include "piece.h"
#include <stdio.h>
#include <wchar.h>

Piece piece_of_char(char p) {
  switch (p) {
  case 'K': return WKing;
  case 'Q': return WQueen;
  case 'R': return WRook;
  case 'B': return WBishop;
  case 'N': return WKnight;
  case 'P': return WPawn;

  case 'k': return BKing;
  case 'q': return BQueen;
  case 'r': return BRook;
  case 'b': return BBishop;
  case 'n': return BKnight;
  case 'p': return BPawn;

  default: return None;
  }
}

static const char* pieces_utf8[13] = {
"·", "♔", "♚", "♕", "♛", "♖", "♜",
"♗", "♝", "♘", "♞", "♙", "♟"
};

const char* pretty_char_of_piece_utf8(Piece p) {
return pieces_utf8[p];
};

static char pieces_char[13] = {' ', 'K', 'k', 'Q', 'q', 'R', 'r',
                               'B', 'b', 'N', 'n', 'P', 'p'};
char char_of_piece(Piece p) { return pieces_char[p]; }


PieceKind piece_kind_of_piece(Piece p) {
  // For exemple, WQueen = 3, (3+1) = 4, 4/2 = 2, 2-1 = 1 = Queen.
  // Similarly, BQueen = 4, (4+1) = 5, 5/2 = 2, 2-1 = 1 = Queen.
  return (PieceKind)((p + 1) / 2 - 1);
}
