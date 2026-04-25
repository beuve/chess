#include "move_list.h"

MoveList ml_empty() {
  return (MoveList) {
    NULL, NULL, 0
  };
}

void ml_push(MoveList* ml, Move elem) {
  MoveListItem* new_elem = malloc(sizeof(MoveListItem));
  new_elem->next = NULL;
  new_elem->m = elem;
  ml->size++;
  if (ml->size == 1) {
    ml->first = new_elem;
    ml->last = new_elem;
    return;
  }
  ml->last->next = new_elem;
  ml->last = new_elem;
}

bool ml_is_empty(MoveList* ml) {
  return !(ml->size);
}

Move ml_pop(MoveList* ml) {
  MoveListItem* removed_elem = ml->first;
  ml->first = ml->first->next;
  Move res = removed_elem->m;
  free(removed_elem);
  ml->size--;
  return res;
}

void ml_append(MoveList* rhs, MoveList* lhs) {
  if (lhs->size == 0) return;
  if (rhs->size == 0) {
    rhs->first = lhs->first;
    rhs->last = lhs->last;
    rhs->size = lhs->size;
    return;
  }
  rhs->last->next = lhs->first;
  rhs->last = lhs->last;
  rhs->size += lhs->size;
}

void ml_clear(MoveList* ml) {
  if (ml->size == 0) return;
  MoveListItem* elem = ml->first;
  while (elem != NULL) {
    MoveListItem* prev_elem = elem;
    elem = prev_elem->next;
    free(prev_elem);
  }
}
