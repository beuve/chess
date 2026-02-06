#ifndef PIECE_H
#define PIECE_H

#include "types.h"
#include <stdint.h>
#include <wchar.h>

typedef enum PieceKind {
  NoPieceKind,
  King,
  Queen,
  Rook,
  Bishop,
  Knight,
  Pawn
} PieceKind;

typedef enum Piece {
  NoPiece,
  WKing,
  BKing,
  WQueen,
  BQueen,
  WRook,
  BRook,
  WBishop,
  BBishop,
  WKnight,
  BKnight,
  WPawn,
  BPawn,
} Piece;

Piece piece_of_char(char p);
char char_of_piece(Piece p);
const char *pretty_char_of_piece(Piece p);

/**
 *  Warning: This function assumes that Piece != NoPiece
 */
PieceKind piece_kind_of_piece(Piece p);
Color color_of_piece(Piece p);
Piece piece_of_piece_kind_color(PieceKind pk, Color c);

#endif
