#include "position.h"

typedef int Zhash;

Zhash Z_NUMBERS[793];

void init_zobrist_numbers (void) __attribute__ ((constructor));
void init_zobrist_numbers();

Zhash zhash_of_position(Position *p);
