// *Really* minimal PCG32 code / (c) 2014 M.E. O'Neill / pcg-random.org
// Licensed under Apache License 2.0 (NO WARRANTY, etc. see website)
#ifndef PCG_H
#define PCG_H

#include <stdint.h>

typedef uint64_t Seed;
typedef struct {
  Seed state;
  Seed inc;
} pcg_t;

uint32_t rand_32(pcg_t *rng);

uint64_t rand_64(pcg_t *rng);

// pcg32_srandom(initstate, initseq)
// pcg32_srandom_r(rng, initstate, initseq):
//     Seed the rng.  Specified in two parts, state initializer and a
//     sequence selection constant (a.k.a. stream id)
void pcg32_srandom_r(pcg_t *rng, Seed initstate, Seed initseq);

#endif
