#include "move.h"
#include "attacks.h"
#include "bitboards.h"
#include "castling.h"
#include "piece.h"
#include "position.h"
#include "types.h"
#include "zobrist.h"
#include <assert.h>
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
  Direction dir = position.turn == White ? Bottom : Top;
  if (file_of_square(move.to) < FH && position.board[move.to + 1] == make_piece(Pawn, !position.turn))
    return move.to + dir;
  if (file_of_square(move.to) > FA && position.board[move.to - 1] == make_piece(Pawn, !position.turn))
    return move.to + dir;
  return NO_SQUARE;
}

ReverseMoveInfos get_reverse_move_infos(Move move, Position *position) {
  return (ReverseMoveInfos){position->castling, position->board[move.to], position->en_passant,
                            position->num_halfmoves};
}

ReverseMoveInfos make_move(Move move, Position *position) {
  ReverseMoveInfos reverse_move_infos = get_reverse_move_infos(move, position);
  position->zhash ^= color_zhash();
  position->num_moves += position->turn;
  position->num_halfmoves = is_halfmove(move, *position) ? position->num_halfmoves + 1 : 0;
  position->zhash ^= zhash_of_en_passant_square(position->en_passant);
  position->en_passant = NO_SQUARE; // Will be set again later if necessary
  position->zhash ^= zhash_of_castling_rights(position->castling);
  position->castling &= castling_update_mask(position, move);
  position->zhash ^= zhash_of_castling_rights(position->castling);

  PieceKind moved_piece_kind = piece_kind_of_piece(position->board[move.from]);
  if (move.kind == CastlingMove) {
    if (move.from == move.to + 2) {
      move_piece(position, move.from, move.from - 2);
      move_piece(position, move.to - 2, move.from - 1);
    } else if (move.from == move.to - 2) {
      move_piece(position, move.from, move.from + 2);
      move_piece(position, move.to + 1, move.from + 1);
    } else {
      assert(false);
    }
  } else if (move.kind == PromotionMove) {
    promote_piece(position, move.from, move.to, move.promoted);
  } else if (move.kind == EnPassantMove) {
    Square captured_square = position->turn == White ? move.to - 8 : move.to + 8;
    move_piece(position, move.from, move.to);
    reverse_move_infos.captured_piece = remove_piece(position, captured_square);
  } else if (moved_piece_kind == Pawn) {
    position->en_passant = en_passant_square_of_move(move, *position);
    position->zhash ^= zhash_of_en_passant_square(position->en_passant);
    move_piece(position, move.from, move.to);
  } else {
    move_piece(position, move.from, move.to);
  }
  position->turn = !position->turn;

  return reverse_move_infos;
}

void undo_move(Move move, Position *position, ReverseMoveInfos reverse_move_infos) {
  position->zhash ^= color_zhash();
  position->turn = !position->turn;
  position->num_moves += position->turn;
  position->num_halfmoves = reverse_move_infos.num_halfmoves;
  position->zhash ^= zhash_of_en_passant_square(position->en_passant);
  position->en_passant = reverse_move_infos.en_passant;
  position->zhash ^= zhash_of_en_passant_square(position->en_passant);
  position->zhash ^= zhash_of_castling_rights(position->castling);
  position->castling = reverse_move_infos.castling;
  position->zhash ^= zhash_of_castling_rights(position->castling);
  if (move.kind == CastlingMove) {
    if (move.from == move.to + 2) {
      move_piece(position, move.from - 2, move.from);
      move_piece(position, move.from - 1, move.to - 2);
    } else if (move.from == move.to - 2) {
      move_piece(position, move.from + 2, move.from);
      move_piece(position, move.from + 1, move.to + 1);
    } else {
      assert(false);
    }
  } else if (move.kind == PromotionMove) {
    unpromote_piece(position, move.to, move.from);
    put_piece(position, move.to, reverse_move_infos.captured_piece);
  } else if (move.kind == EnPassantMove) {
    Square captured_square = position->turn == White ? move.to - 8 : move.to + 8;
    move_piece(position, move.to, move.from);
    put_piece(position, captured_square, reverse_move_infos.captured_piece);
  } else {
    move_piece(position, move.to, move.from);
    put_piece(position, move.to, reverse_move_infos.captured_piece);
  }
}

bool is_legal(Move mv, Position pos) {
  Square king_sq = pos.kings[pos.turn];
  if (mv.kind == EnPassantMove) {
    Square captured_square = pawn_push(mv.to, !pos.turn);
    BB mask = (bb_all_pieces(pos.bitboards) ^ (1ll << mv.from) ^ (1ll << captured_square)) | (1ll << mv.to);
    return !is_square_attacked(king_sq, pos.bitboards, !pos.turn, mask, captured_square);
  }
  if (mv.kind == CastlingMove) return true; // Already checked in movegen
  BB mask = (bb_all_pieces(pos.bitboards) ^ (1ll << mv.from)) | 1ll << mv.to;
  if (mv.from == king_sq) {
    return !is_square_attacked(mv.to, pos.bitboards, !pos.turn, mask, mv.to);
  }
  return !is_square_attacked(king_sq, pos.bitboards, !pos.turn, mask, mv.to);
}
