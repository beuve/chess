#include "bitboards.h"
#include "piece.h"
#include <stdlib.h>
#include <string.h>

BB bb_all_pieces(Bitboards bbs) { return bbs.blacks | bbs.whites; }

BB bb_all_of_color(Bitboards bbs, Color c) { return c ? bbs.blacks : bbs.whites; }

BB bb_all_of_piece(Bitboards bbs, PieceKind pk) {
  switch (pk) {
  case King: return bbs.kings;
  case Queen: return bbs.queens;
  case Rook: return bbs.rooks;
  case Bishop: return bbs.bishops;
  case Knight: return bbs.knights;
  case Pawn: return bbs.pawns;
  case NO_PIECE_KIND: return 0ll;
  }
}

BB bb_color_pieces(Bitboards bbs, Color c, PieceKind pk) {
  BB bb_color = bb_all_of_color(bbs, c);
  BB bb_piece = bb_all_of_piece(bbs, pk);
  return bb_color & bb_piece;
}

void init_botboards_from_mailbox(Piece board[64], Bitboards *bbs) {
  for (Square sq = A1; sq <= H8; sq++) {
    if (board[sq] == NO_PIECE) continue;
    BB bb_sq = 1ll << sq;
    Color c = color_of_piece(board[sq]);
    switch (c) {
    case White: bbs->whites |= bb_sq; break;
    case Black: bbs->blacks |= bb_sq; break;
    }
    PieceKind pk = piece_kind_of_piece(board[sq]);
    switch (pk) {
    case King: bbs->kings |= bb_sq; break;
    case Queen: bbs->queens |= bb_sq; break;
    case Rook: bbs->rooks |= bb_sq; break;
    case Knight: bbs->knights |= bb_sq; break;
    case Bishop: bbs->bishops |= bb_sq; break;
    case Pawn: bbs->pawns |= bb_sq; break;
    case NO_PIECE_KIND: break;
    }
  }
}

int bb_serialize(BB bb, Square **result) {
  Square temp_result[64] = {0};
  int size = 0;
  for (Square sq = A1; sq <= H8; sq++) {
    BB bb_sq = 1ll << sq;
    if (bb & bb_sq) {
      temp_result[size] = sq;
      size++;
    }
  }
  *result = malloc(size * sizeof(Square));
  memcpy(*result, temp_result, size * sizeof(Square));
  return size;
}

void bb_switch_piece(Bitboards *bbs, Piece piece, Square sq) {
  PieceKind pk = piece_kind_of_piece(piece);
  switch (pk) {
  case King: bbs->kings ^= 1ll << sq; break;
  case Queen: bbs->queens ^= 1ll << sq; break;
  case Rook: bbs->rooks ^= 1ll << sq; break;
  case Bishop: bbs->bishops ^= 1ll << sq; break;
  case Knight: bbs->knights ^= 1ll << sq; break;
  case Pawn: bbs->pawns ^= 1ll << sq; break;
  case NO_PIECE_KIND: return; // If no piece, then don't change the colors
  };
  Color c = color_of_piece(piece);
  switch (c) {
  case White: bbs->whites ^= 1ll << sq; break;
  case Black: bbs->blacks ^= 1ll << sq; break;
  };
}
