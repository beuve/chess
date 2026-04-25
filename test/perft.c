#include "perft.h"
#include "fen.h"
#include "test.h"

int position1() {
  char *fen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
  Position p = position_of_fen(fen);
  ASSERT_EQ(perft(&p, 1, false), 20, "Position 1: failed perft 1");
  ASSERT_EQ(perft(&p, 2, false), 400, "Position 1: failed perft 2");
  ASSERT_EQ(perft(&p, 3, false), 8902, "Position 1: failed perft 3");
  ASSERT_EQ(perft(&p, 4, false), 197281, "Position 1: failed perft 4");
  ASSERT_EQ(perft(&p, 5, false), 4865609, "Position 1: failed perft 5");
  return 0;
}

int position2() {
  char *fen = "r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq - 0 1";
  Position p = position_of_fen(fen);
  ASSERT_EQ(perft(&p, 1, false), 48, "Position 2: failed perft 1");
  ASSERT_EQ(perft(&p, 2, false), 2039, "Position 2: failed perft 2");
  ASSERT_EQ(perft(&p, 3, false), 97862, "Position 2: failed perft 3");
  ASSERT_EQ(perft(&p, 4, false), 4085603, "Position 2: failed perft 4");
  return 0;
}

int position3() {
  char *fen = "8/2p5/3p4/KP5r/1R3p1k/8/4P1P1/8 w - - 0 1";
  Position p = position_of_fen(fen);
  ASSERT_EQ(perft(&p, 1, false), 14, "Position 3: failed perft 1");
  ASSERT_EQ(perft(&p, 2, false), 191, "Position 3: failed perft 2");
  ASSERT_EQ(perft(&p, 3, false), 2812, "Position 3: failed perft 3");
  ASSERT_EQ(perft(&p, 4, false), 43238, "Position 3: failed perft 4");
  ASSERT_EQ(perft(&p, 5, false), 674624, "Position 3: failed perft 5");
  ASSERT_EQ(perft(&p, 6, false), 11030083, "Position 3: failed perft 6");
  return 0;
}

int position4() {
  char *fen = "r3k2r/Pppp1ppp/1b3nbN/nP6/BBP1P3/q4N2/Pp1P2PP/R2Q1RK1 w kq - 0 1";
  Position p = position_of_fen(fen);
  ASSERT_EQ(perft(&p, 1, false), 6, "Position 4: failed perft 1");
  ASSERT_EQ(perft(&p, 2, false), 264, "Position 4: failed perft 2");
  ASSERT_EQ(perft(&p, 3, false), 9467, "Position 4: failed perft 3");
  ASSERT_EQ(perft(&p, 4, false), 422333, "Position 4: failed perft 4");
  ASSERT_EQ(perft(&p, 5, false), 15833292, "Position 4: failed perft 5");
  return 0;
}

int position5() {
  char *fen = "rnbq1k1r/pp1Pbppp/2p5/8/2B5/8/PPP1NnPP/RNBQK2R w KQ - 1 8";
  Position p = position_of_fen(fen);
  ASSERT_EQ(perft(&p, 1, false), 44, "Position 5: failed perft 1");
  ASSERT_EQ(perft(&p, 2, false), 1486, "Position 5: failed perft 2");
  ASSERT_EQ(perft(&p, 3, false), 62379, "Position 5: failed perft 3");
  ASSERT_EQ(perft(&p, 4, false), 2103487, "Position 5: failed perft 4");
  return 0;
}

int position6() {
  char *fen = "r4rk1/1pp1qppp/p1np1n2/2b1p1B1/2B1P1b1/P1NP1N2/1PP1QPPP/R4RK1 w - - 0 10";
  Position p = position_of_fen(fen);
  ASSERT_EQ(perft(&p, 1, false), 46, "Position 5: failed perft 1");
  ASSERT_EQ(perft(&p, 2, false), 2079, "Position 5: failed perft 2");
  ASSERT_EQ(perft(&p, 3, false), 89890, "Position 5: failed perft 3");
  ASSERT_EQ(perft(&p, 4, false), 3894594, "Position 5: failed perft 4");
  return 0;
}

int main() {
  int res = 0;
  res |= position1();
  res |= position2();
  res |= position3();
  res |= position4();
  res |= position5();
  res |= position6();
  return res;
}
