#include "pcg.h"

uint32_t rand_32(pcg_t *rng) {
  uint64_t oldstate = rng->state;
  // Advance internal state
  rng->state = oldstate * 6364136223846793005ULL + (rng->inc | 1);
  // Calculate output function (XSH RR), uses old state for max ILP
  uint32_t xorshifted = ((oldstate >> 18u) ^ oldstate) >> 27u;
  uint32_t rot = oldstate >> 59u;
  return (xorshifted >> rot) | (xorshifted << ((-rot) & 31));
}

uint64_t rand_64(pcg_t *rng) {
  uint64_t high = rand_32(rng);
  uint64_t low = rand_32(rng);
  return (high << 32) | low;
}

void pcg32_srandom_r(pcg_t *rng, Seed initstate, Seed initseq) {
  rng->state = 0U;
  rng->inc = (initseq << 1u) | 1u;
  rand_32(rng);
  rng->state += initstate;
  rand_32(rng);
}
