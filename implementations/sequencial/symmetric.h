#ifndef SYMMETRIC_H
#define SYMMETRIC_H

#include "fips202.h"
#include "params.h"
#include <stdint.h>
#include <stdlib.h>

// XOF state
typedef struct {
  keccak_state s;
} xof_state;

// XOF functions
void xof_absorb(xof_state *state, const uint8_t seed[KYBER_SYMBYTES], uint8_t x,
                uint8_t y);
void xof_squeezeblocks(uint8_t *out, size_t nblocks, xof_state *state);
void xof_ctx_release(xof_state *state);

// PRF for noise sampling
void prf(uint8_t *out, size_t outlen, const uint8_t key[KYBER_SYMBYTES],
         uint8_t nonce);

// Random bytes (system RNG)
void randombytes(uint8_t *out, size_t outlen);

#endif
