#include "fen.h"
#include "position.h"
#include <locale.h>
#include <stdio.h>
#include <wchar.h>

int main() {
  setlocale(LC_ALL, "");
  Position p = position_of_fen(
      "rnb1kbnr/ppp1qppp/8/3p4/4P3/8/PPPP1PPP/RNBQKBNR w KQkq - 0 2");
  print_position(&p);
  printf("%s\n", fen_of_position(&p));
  return 0;
}
