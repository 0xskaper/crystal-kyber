#ifndef SYMMETRIC_H
#define SYMMETRIC_H

#include "params.h"
#include <stddef.h>
#include <stdint.h>

void sha3_256(uint8_t *h, const uint8_t *in, size_t inlen);
void sha3_512(uint8_t *h, const uint8_t *in, size_t inlen);
void shake128(uint8_t *out, size_t outlen, const uint8_t *in, size_t inlen);
void shake256(uint8_t *out, size_t outlen, const uint8_t *in, size_t inlen);

// XDF for sampling polynomials
typedef struct {
  uint64_t state[25];
  uint8_t buffer[SHAKE128_RATE];
  size_t pos;
} xof_state;

void xof_absorb(xof_state *state, const uint8_t seed[KYBER_SYMBYTES], uint8_t x,
                uint8_t y);
void xof_squeezeblocks(uint8_t *out, size_t nblocks, xof_state *state);
void xof_ctx_release(xof_state *state);

// PRF for generating noise
void prf(uint8_t *out, size_t outlen, const uint8_t key[KYBER_SYMBYTES],
         uint8_t nonce);
void randomBytes(uint8_t *out, size_t outlen);

#endif
