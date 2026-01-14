#include <stdint.h>

typedef uint64_t BB;

typedef struct Bitboards {
  BB whites;
  BB blacks;

  BB kings;
  BB kinghts;
  BB rooks;
  BB queens;
  BB bishops;
} Bitboards;
