#include "pretty_print.h"
#include "position.h"
#include <stdlib.h>

static const char *pieces_utf8[13] = {"·", "♚", "♔", "♛", "♕", "♜", "♖", "♝", "♗", "♞", "♘", "♟", "♙"};

const char *pretty_char_of_piece(Piece p) { return pieces_utf8[p]; };

void char_of_square(Square sq, char *buffer) {
  buffer[0] = file_of_square(sq) + 97;
  buffer[1] = rank_of_square(sq) + 49;
  buffer[2] = '\0';
}

void print_position(Position *position) {
  for (int rk = R8; rk >= R1; rk--) {
    printf("%d ", rk + 1);
    for (File fl = FA; fl <= FH; fl++) {
      Square sq = square_of_rk_fl(rk, fl);
      printf("%s ", pretty_char_of_piece(position->board[sq]));
    }
    printf("\n");
  }
  printf("  A B C D E F G H\n");
}

void print_bitboard(BB bb) {
  for (int rk = R8; rk >= R1; rk--) {
    printf("%d ", rk + 1);
    for (File fl = FA; fl <= FH; fl++) {
      Square sq = square_of_rk_fl(rk, fl);
      printf("%s ", (bb & 1ll << sq) ? "•" : "·");
    }
    printf("\n");
  }
  printf("  A B C D E F G H\n");
}
