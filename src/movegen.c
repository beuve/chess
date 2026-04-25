#include "movegen.h"
#include "attacks.h"
#include "bitboards.h"
#include "castling.h"
#include "move.h"
#include "move_list.h"
#include "piece.h"
#include "position.h"
#include "types.h"
#include <stdlib.h>
#include <string.h>

void register_attacking_moves(Position pos, BB attacking_bb, MoveList *ml, Square from) {
  Square *attacked_sq;
  BB player_bb = bb_all_of_color(pos.bitboards, pos.turn);
  BB attacked_bb = attacking_bb ^ (attacking_bb & player_bb);
  int num_attacks = bb_serialize(attacked_bb, &attacked_sq);
  for (int m = 0; m < num_attacks; m++) {
    ml_push(ml, (Move){from, attacked_sq[m], NormalMove, NO_PIECE_KIND});
  }
}

MoveList list_king_moves(Position pos) {
  MoveList moves = ml_empty();
  Square king_sq = pos.kings[pos.turn];

  BB king_attacks_bb = get_king_attacks(king_sq);
  register_attacking_moves(pos, king_attacks_bb, &moves, king_sq);

  if (can_castle_king_side(pos, pos.turn)) {
    ml_push(&moves, (Move){king_sq, king_sq + 2, CastlingMove, NO_PIECE_KIND});
  }
  if (can_castle_queen_side(pos, pos.turn)) {
    ml_push(&moves, (Move){king_sq, king_sq - 2, CastlingMove, NO_PIECE_KIND});
  }

  return moves;
}

MoveList list_rooks_moves(Position pos) {
  MoveList moves = ml_empty();
  BB rooks_bb = bb_color_pieces(pos.bitboards, pos.turn, Rook);
  BB queens_bb = bb_color_pieces(pos.bitboards, pos.turn, Queen);
  Square *rooks_queens_sq;
  int num_rooks_queens = bb_serialize(rooks_bb | queens_bb, &rooks_queens_sq);
  for (int r = 0; r < num_rooks_queens; r++) {
    BB rook_queens_attacks_bb = get_rook_attacks(rooks_queens_sq[r], bb_all_pieces(pos.bitboards));
    register_attacking_moves(pos, rook_queens_attacks_bb, &moves, rooks_queens_sq[r]);
  }
  return moves;
}

MoveList list_bishops_moves(Position pos) {
  MoveList moves = ml_empty();
  BB bishops_bb = bb_color_pieces(pos.bitboards, pos.turn, Bishop);
  BB queens_bb = bb_color_pieces(pos.bitboards, pos.turn, Queen);
  Square *bishops_queens_sq;
  int num_bishops_queens = bb_serialize(bishops_bb | queens_bb, &bishops_queens_sq);
  for (int r = 0; r < num_bishops_queens; r++) {
    BB bishop_queen_attacks_bb = get_bishop_attacks(bishops_queens_sq[r], bb_all_pieces(pos.bitboards));
    register_attacking_moves(pos, bishop_queen_attacks_bb, &moves, bishops_queens_sq[r]);
  }
  return moves;
}

MoveList list_knights_moves(Position pos) {
  MoveList moves = ml_empty();
  BB knights_bb = bb_color_pieces(pos.bitboards, pos.turn, Knight);
  Square *knights_sq;
  int num_knights = bb_serialize(knights_bb, &knights_sq);
  for (int r = 0; r < num_knights; r++) {
    BB knight_attacks_bb = get_knight_attacks(knights_sq[r]);
    register_attacking_moves(pos, knight_attacks_bb, &moves, knights_sq[r]);
  }
  return moves;
}

/**
 */
MoveList list_single_pawns_move(Position pos, Square from, Square to) {
  MoveList moves = ml_empty();
  Piece attacking_pc = pos.board[from];
  if (attacking_pc != make_piece(Pawn, pos.turn)) return moves;
  bool is_white_promotion = !pos.turn && rank_of_square(to) == R8;
  bool is_black_promotion = pos.turn && rank_of_square(to) == R1;
  if (to == pos.en_passant) {
    ml_push(&moves, (Move){from, to, EnPassantMove, NO_PIECE_KIND});
  } else if (is_white_promotion || is_black_promotion) {
    ml_push(&moves, (Move){from, to, PromotionMove, Queen});
    ml_push(&moves, (Move){from, to, PromotionMove, Rook});
    ml_push(&moves, (Move){from, to, PromotionMove, Bishop});
    ml_push(&moves, (Move){from, to, PromotionMove, Knight});
  } else {
    ml_push(&moves, (Move){from, to, NormalMove, NO_PIECE_KIND});
  }
  return moves;
}

MoveList list_pawns_attacks(Position pos) {
  MoveList moves = ml_empty();
  BB pawns_bb = bb_color_pieces(pos.bitboards, pos.turn, Pawn);
  BB pawns_attacks_bb = get_pawns_attacks(pawns_bb, pos.turn);
  BB opponent_bb = bb_all_of_color(pos.bitboards, !pos.turn);
  BB en_passant_bb = pos.en_passant == NO_SQUARE ? 0ll : 1ll << pos.en_passant;
  BB pawns_attacked_bb = pawns_attacks_bb & (opponent_bb | en_passant_bb);
  Direction push_direction = pos.turn ? Bottom : Top;

  Square *pawns_attacked_sq;
  int num_attacks = bb_serialize(pawns_attacked_bb, &pawns_attacked_sq);
  for (int m = 0; m < num_attacks; m++) {
    Square attacked_sq = pawns_attacked_sq[m];
    // An attacked square can be attacked from two sides.
    // Attacked from the right
    if (file_of_square(attacked_sq) != FH) {
      Square attacking_sq = attacked_sq - push_direction + 1;
      MoveList attacks = list_single_pawns_move(pos, attacking_sq, attacked_sq);
      ml_append(&moves, &attacks);
    }
    // Attacked from the left
    if (file_of_square(attacked_sq) != FA) {
      Square attacking_sq = attacked_sq - push_direction - 1;
      MoveList attacks = list_single_pawns_move(pos, attacking_sq, attacked_sq);
      ml_append(&moves, &attacks);
    }
  }
  return moves;
}

MoveList list_single_pawns_push(Position pos, Square attacking_sq, Square attacked_sq) {
  MoveList moves = ml_empty();
  Piece attacking_pc = pos.board[attacking_sq];
  if (attacking_pc != make_piece(Pawn, pos.turn)) return moves;

  if (attacked_sq > attacking_sq && rank_of_square(attacked_sq) == R8) {
    ml_push(&moves, (Move){attacking_sq, attacked_sq, PromotionMove, Queen});
    ml_push(&moves, (Move){attacking_sq, attacked_sq, PromotionMove, Rook});
    ml_push(&moves, (Move){attacking_sq, attacked_sq, PromotionMove, Bishop});
    ml_push(&moves, (Move){attacking_sq, attacked_sq, PromotionMove, Knight});
  } else {
    ml_push(&moves, (Move){attacking_sq, attacked_sq, NormalMove, NO_PIECE_KIND});
  }
  return moves;
}

MoveList list_pawns_pushes(Position pos) {
  MoveList moves = ml_empty();
  BB pawns_bb = bb_color_pieces(pos.bitboards, pos.turn, Pawn);
  Square *pawns_sq;
  int num_pawns = bb_serialize(pawns_bb, &pawns_sq);
  for (int i = 0; i < num_pawns; i++) {
    Square pawn_sq = pawns_sq[i];
    Square pushed_pawn_sq = pawn_push(pawn_sq, pos.turn);
    if (!(bb_all_pieces(pos.bitboards) & (1ll << pushed_pawn_sq))) {
      MoveList pushes = list_single_pawns_move(pos, pawn_sq, pushed_pawn_sq);
      ml_append(&moves, &pushes);
      if (pawn_is_origin_square(pawn_sq, pos.turn)) {
        Square double_pushed_pawn_sq = pawn_push(pushed_pawn_sq, pos.turn);
        if (!(bb_all_pieces(pos.bitboards) & (1ll << double_pushed_pawn_sq))) {
          ml_push(&moves, (Move){pawn_sq, double_pushed_pawn_sq, NormalMove, NO_PIECE_KIND});
        }
      }
    }
  }
  return moves;
}

MoveList list_pawns_moves(Position pos) {
  MoveList moves = ml_empty();
  MoveList pushes = list_pawns_pushes(pos);
  ml_append(&moves, &pushes);
  MoveList attacks = list_pawns_attacks(pos);
  ml_append(&moves, &attacks);
  return moves;
}

MoveList list_pseudo_legal_moves(Position pos) {
  MoveList moves = ml_empty();
  MoveList king = list_king_moves(pos);
  ml_append(&moves, &king);
  MoveList rooks = list_rooks_moves(pos);
  ml_append(&moves, &rooks);
  MoveList bishops = list_bishops_moves(pos);
  ml_append(&moves, &bishops);
  MoveList knights = list_knights_moves(pos);
  ml_append(&moves, &knights);
  MoveList pawns = list_pawns_moves(pos);
  ml_append(&moves, &pawns);
  return moves;
}
