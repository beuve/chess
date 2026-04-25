#ifndef MOVEGEN_H
#define MOVEGEN_H

#include "move_list.h"

MoveList list_king_moves(Position);
MoveList list_rooks_moves(Position);
MoveList list_bishops_moves(Position);
MoveList list_knights_moves(Position);
MoveList list_pawns_moves(Position); 
MoveList list_pseudo_legal_moves(Position);
#endif
