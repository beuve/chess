#include <stdint.h>
#include <wchar.h>

typedef enum PieceKind { King, Quenn, Rook, Bishop, Knight } PieceKind;

typedef enum Piece {
  None,
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
wchar_t pretty_char_of_piece(Piece p);
const char* pretty_char_of_piece_utf8(Piece p) ;
/**
 *  Warning: This function assumes that Piece != Empty
 */
PieceKind piece_kind_of_piece(Piece p);
