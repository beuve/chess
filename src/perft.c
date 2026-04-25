#include "perft.h"
#include "move.h"
#include "move_list.h"
#include "movegen.h"
#include "pretty_print.h"
#include <stdint.h>

void print_step(Square from, Square to, uint64_t count) {
  char f[3], t[3];
  char_of_square(from, f);
  char_of_square(to, t);
  fprintf(stderr, "%s%s: %lld\n", f, t, count);
}

uint64_t perft(Position *pos, int depth, bool print) {
  MoveList moves = list_pseudo_legal_moves(*pos);
  uint64_t total = 0;
  while (moves.size != 0) {
    Move move = ml_pop(&moves);
    if (!is_legal(move, *pos)) continue;
    uint64_t count = 1;
    if (depth != 1) {
      ReverseMoveInfos reverse_infos = make_move(move, pos);
      count = perft(pos, depth - 1, false);
      undo_move(move, pos, reverse_infos);
    }
    if (print) print_step(move.from, move.to, count);
    total += count;
  }
  return total;
}
