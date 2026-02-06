#ifndef MOVE_H
#define MOVE_H

#include "piece.h"
#include "position.h"
#include "types.h"

typedef enum MoveKind {
  NormalMove,
  PromotionMove,
  EnPassantMove,
  CastlingMove
} MoveKind;

typedef struct Move {
  Square from;
  Square to;
  MoveKind kind;
  PieceKind promoted;
} Move;

bool is_halfmove(Move move, Position position);
// bool is_legal(Move move, Position pos);
void make_move(Move move, Position *position);
Square en_passant_square(Move move, Position position);
// undo_move

#endif
