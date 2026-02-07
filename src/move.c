#include "move.h"
#include "castling.h"
#include "piece.h"
#include "position.h"
#include "types.h"
#include "zobrist.h"
#include <stdlib.h>

bool is_halfmove(Move move, Position position) {
  PieceKind moved_piece = piece_kind_of_piece(position.board[move.from]);
  if (moved_piece == Pawn) return false;
  if (move.kind == CastlingMove) return true;
  if (move.kind == EnPassantMove) return false;
  if (position.board[move.to] != NO_PIECE) return false;
  return true;
}

Square en_passant_square_of_move(Move move, Position position) {
  int diff = move.from > move.to ? move.from - move.to : move.to - move.from;
  if (diff != 16) return NO_SQUARE;
  Square to = move.to;
  if (file_of_square(to) < FH && position.board[move.to + 1] == make_piece(Pawn, !position.turn)) return move.to;
  if (file_of_square(to) > FA && position.board[move.to - 1] == make_piece(Pawn, !position.turn)) return move.to;
  return NO_SQUARE;
}

void make_move(Move move, Position *position) {
  position->zhash ^= color_zhash();
  position->num_moves += position->turn;
  position->num_halfmoves = is_halfmove(move, *position) ? position->num_halfmoves + 1 : 0;
  position->zhash ^= zhash_of_en_passant_square(position->en_passant);
  position->en_passant = NO_SQUARE; // Will be set again later if necessary
  position->zhash ^= zhash_of_castling_rights(position->castling);
  position->castling &= castling_update_mask(position, move);
  position->zhash ^= zhash_of_castling_rights(position->castling);

  PieceKind moved_piece_kind = piece_kind_of_piece(position->board[move.from]);
  if (moved_piece_kind == King) {
    if (move.kind == CastlingMove && move.from == move.to + 4) {
      move_piece(position, move.from, move.from - 2);
      move_piece(position, move.to, move.from - 1);
    } else if (move.kind == CastlingMove && move.from == move.to + 4) {
      move_piece(position, move.from, move.from + 2);
      move_piece(position, move.to, move.from + 1);
    } else {
      move_piece(position, move.from, move.to);
    }
  } else if (move.kind == PromotionMove) {
    promote_piece(position, move.from, move.to, move.promoted);
  } else if (move.kind == EnPassantMove) {
    Square captured_square = position->turn ? move.to + 8 : move.to - 8;
    move_piece(position, move.from, move.to);
    remove_piece(position, captured_square);
  } else if (moved_piece_kind == Pawn) {
    position->en_passant = en_passant_square_of_move(move, *position);
    position->zhash ^= zhash_of_en_passant_square(position->en_passant);
    move_piece(position, move.from, move.to);
  } else {
    move_piece(position, move.from, move.to);
  }
  position->turn = !position->turn;
}
