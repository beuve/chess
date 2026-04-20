#ifndef MOVE_H
#define MOVE_H

#include "piece.h"
#include "position.h"
#include "types.h"

// clang-format off
typedef enum MoveKind {
  NormalMove,
  PromotionMove,
  EnPassantMove,
  CastlingMove
} MoveKind;
// clang-format on

typedef struct ReverseMoveInfos {
  CastlingRights castling;
  Piece captured_piece;
  Square en_passant;
  int num_halfmoves;
} ReverseMoveInfos;

typedef struct Move {
  Square from;
  Square to;
  MoveKind kind;
  PieceKind promoted;
} Move;

bool is_halfmove(Move, Position);
// bool is_legal(Move move, Position pos);
ReverseMoveInfos make_move(Move, Position*);
Square en_passant_square(Move, Position);
void undo_move(Move, Position*, ReverseMoveInfos);

#endif
