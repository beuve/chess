#ifndef FEN_H
#define FEN_H

#include "position.h"

Position position_of_fen(char *fen);
char *fen_of_position(Position *position);

#endif
