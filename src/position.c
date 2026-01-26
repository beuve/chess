#include "position.h"
#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>


void print_position(Position position) {
  for (Square sq = A8; sq <= H1; sq++) {
    if (sq % 8 == 0) printf("%d ", 8 - (sq / 8));
    printf("%s ", pretty_char_of_piece_utf8(position.board[sq]));
    if (sq % 8 == 7) printf("\n");
  }
  printf("  A B C D E F G H\n");
}

Position position_of_fen(char *fen) {
  Position position = {0};
  Square sq = A8;
  while (*fen != ' ') {
    if (*fen == '/') {
    } else if (isdigit(*fen)) {
      sq += *fen - '0';
    } else {
      position.board[sq] = piece_of_char(*fen);
      sq++;
    }
    fen++;
    assert(sq <= H1 || *fen == ' ');
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
    char col = (int)(*fen - 'a');
    char row = (int)(*++fen - '0');
    position.en_passant = (Square)(col + 8 * (8-row));
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
  int cum = 0;
  for (Square sq = A8; sq <= H1; sq++) {
    if (position->board[sq] == None) {
      cum++;
    } else {
      if (cum > 0) {
        fen[fen_len++] = '0' + cum;
        cum = 0;
      }
      fen[fen_len++] = char_of_piece(position->board[sq]);
    }
    if (sq % 8 == 7) {
      if (cum > 0) {
        fen[fen_len++] = '0' + cum;
        cum = 0;
      }
      if (sq != H1) {
        fen[fen_len++] = '/';
      }
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
    char row = position->en_passant / 8 + '0';
    fen[fen_len++] = row;
  }

  fen[fen_len] = '\0';
  sprintf(fen + fen_len, " %d %d", position->num_halfmoves,
          position->num_moves);

  char *res = (char *)malloc(sizeof(char) * (strlen(fen) + 1));
  strcpy(res, fen);
  return res;
}
