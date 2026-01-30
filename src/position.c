#include "position.h"
#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>

void print_position(Position *position) { 
  for (int rk = R8; rk >= R1; rk--) {
    printf("%d ", 8 - rk);
    for (File fl = FA; fl <= FH; fl++) {
      Square sq = square_of_rk_fl(7 - rk, fl);
      printf("%s ", pretty_char_of_piece_utf8(position->board[sq]));
    }
    printf("\n");
  }
  printf("  A B C D E F G H\n");
}

Position position_of_fen(char *fen) {
  Position position = {0};
  File fl = FA;
  Rank rk = R8;
  while (*fen != ' ') {
    Square sq = square_of_rk_fl(rk, fl);
    if (*fen == '/') {
      rk--;
      fl = 0;
    } else if (isdigit(*fen)) {
      fl += *fen - '0';
    } else {
      position.board[sq] = piece_of_char(*fen);
      fl++;
    }
    fen++;
  }

  position.turn = *++fen == 'b';

  fen++;
  assert(*fen++ == ' ');

  position.castling = 0;
  while (*fen != ' ') {
    switch (*fen) {
    case 'K': position.castling += 0b0001; break;
    case 'Q': position.castling += 0b0010; break;
    case 'k': position.castling += 0b0100; break;
    case 'q': position.castling += 0b1000; break;
    }
    fen++;
  }

  if (*++fen == '-') {
    position.en_passant = NO_SQUARE;
  } else {
    File fl = (int)(*fen - 'a');
    Rank rk = (int)(*++fen - '1');
    position.en_passant = square_of_rk_fl(rk, fl);
  }

  fen++;
  assert(*fen++ == ' ');
  position.num_halfmoves = strtol(fen, &fen, 10);
  assert(*fen++ == ' ');
  position.num_moves = strtol(fen, &fen, 10);

  return position;
}

char *fen_of_position(Position *position) {
  char fen[100] = "";
  int fen_len = 0;
  for (int rk = R8; rk >= R1; rk--) {
    int cum = 0;
    for (File fl = FA; fl <= FH; fl ++) {
      Square sq = square_of_rk_fl(rk, fl);
      if (position->board[sq] == None) {
        cum++;
      } else {
        if (cum > 0) {
          fen[fen_len++] = '0' + cum;
          cum = 0;
        }
        fen[fen_len++] = char_of_piece(position->board[sq]);
      }
    }
    if (cum > 0) {
      fen[fen_len++] = '0' + cum;
      cum = 0;
    }
    if (rk != R1) {
      fen[fen_len++] = '/';
    }
  }

  fen[fen_len++] = ' ';
  fen[fen_len++] = position->turn ? 'b' : 'w';

  fen[fen_len++] = ' ';
  if (position->castling & 0b0001) fen[fen_len++] = 'K';
  if (position->castling & 0b0010) fen[fen_len++] = 'Q';
  if (position->castling & 0b0100) fen[fen_len++] = 'k';
  if (position->castling & 0b1000) fen[fen_len++] = 'q';

  fen[fen_len++] = ' ';
  if (position->en_passant == NO_SQUARE) {
    fen[fen_len++] = '-';
  } else {
    char col = position->en_passant % 8 + 'a';
    fen[fen_len++] = col;
    char row = position->en_passant / 8 + '1';
    fen[fen_len++] = row;
  }

  fen[fen_len] = '\0';
  sprintf(fen + fen_len, " %d %d", position->num_halfmoves,
          position->num_moves);

  char *res = (char *)malloc(sizeof(char) * (strlen(fen) + 1));
  strcpy(res, fen);
  return res;
}

Square square_of_rk_fl(Rank rk, File fl){
  return rk * 8 + fl;
}

Rank rank_of_square(Square sq) {
  return sq / 8;
}

File file_of_square(Square sq) {
  return sq % 8;
}
