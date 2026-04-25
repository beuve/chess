#ifndef MOVE_LIST_H
#define MOVE_LIST_H

#include "move.h"
#include <stdlib.h>

typedef struct MoveListItem {
  Move m;
  struct MoveListItem* next;
} MoveListItem;

typedef struct MoveList {
  MoveListItem *first;
  MoveListItem *last;
  int size;
} MoveList;

MoveList ml_empty();

void ml_push(MoveList*, Move);

bool ml_is_empty(MoveList*);

Move ml_pop(MoveList*);

void ml_append(MoveList* rhs, MoveList* lhs);

int ml_size(MoveList);

void ml_clear(MoveList*);

#endif
