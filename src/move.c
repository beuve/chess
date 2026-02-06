#include "move.h"
#include "castling.h"
#include "piece.h"

bool is_halfmove(Move move, Position position) {
  PieceKind moved_piece = piece_kind_of_piece(position.board[move.from]);
  if (moved_piece == Pawn) return false;
  if (moved_piece == King && can_castle(position, position.turn)) return false;
  if (moved_piece == Rook) {
    if (move.from % 8 == 0 && can_castle_king_side(position, position.turn))
      return false;
    if (move.from % 8 == 7 && can_castle_queen_side(position, position.turn))
      return false;
  }
  return true;
}
