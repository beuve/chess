#include "fen.h"
#include "position.h"
#include <locale.h>
#include <stdio.h>
#include <wchar.h>

int main() {
  setlocale(LC_ALL, "");
  Position p = position_of_fen(
      "rnbqkbnr/ppp2ppp/3p4/8/3Pp3/1P3N2/P1P1PPPP/RNBQKBR1 b Qkq d3 0 4");
  print_position(&p);
  printf("%s\n", fen_of_position(&p));
  return 0;
}
