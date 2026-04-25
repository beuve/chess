#ifndef BITBOARD_H
#define BITBOARD_H

#include "piece.h"
#include "types.h"

typedef struct Bitboards {
  BB whites;
  BB blacks;

  BB kings;
  BB knights;
  BB rooks;
  BB queens;
  BB bishops;
  BB pawns;
} Bitboards;

void init_botboards_from_mailbox(Piece board[64], Bitboards*);

int bb_serialize(BB bb, Square **result);
BB bb_all_pieces(Bitboards);
BB bb_all_of_color(Bitboards, Color);
BB bb_all_of_piece(Bitboards, PieceKind);
BB bb_color_pieces(Bitboards, Color, PieceKind);
void bb_switch_piece(Bitboards *bbs, Piece piece, Square sq);
#endif
