#include "castling.h"
#include "fen.h"
#include "movegen.h"
#include "pretty_print.h"
#include "perft.h"
#include "position.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>

int main() {
  char *starting_fen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
  Position p = position_of_fen(starting_fen);
  print_position(&p);
  print_bitboard(p.bitboards.kings);
  uint64_t perft_result = perft(&p, 7, true);
  fprintf(stderr, "perft = %lld\n", perft_result);
  return 0;
}
