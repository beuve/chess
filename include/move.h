#ifndef MOVE_H
#define MOVE_H

#include "piece.h"
#include "position.h"
#include "types.h"

typedef enum MoveKind {
  NormalMove,
  PromotionMove,
  EnPassant,
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
// bool make_move(Move move, Position pos);
// undo_move

#endif
