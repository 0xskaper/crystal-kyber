#include "symmetric.h"
#include "fips202.h"
#include "params.h"
#include <stdlib.h>
#include <string.h>
#include <time.h> // For time()

/*
 * Initialize XOF state with seed and domain separators
 */
void xof_absorb(xof_state *state, const uint8_t seed[KYBER_SYMBYTES], uint8_t x,
                uint8_t y) {
  uint8_t buf[KYBER_SYMBYTES + 2];

  memcpy(buf, seed, KYBER_SYMBYTES);
  buf[KYBER_SYMBYTES] = x;
  buf[KYBER_SYMBYTES + 1] = y;

  shake128_absorb(&state->s, buf, KYBER_SYMBYTES + 2);
}

/*
 * Generate XOF output blocks
 */
void xof_squeezeblocks(uint8_t *out, size_t nblocks, xof_state *state) {
  shake128_squeezeblocks(out, nblocks, &state->s);
}

/*
 * Release XOF state
 */
void xof_ctx_release(xof_state *state) {
  // Nothing to release in this implementation
  (void)state;
}

/*
 * PRF for generating noise
 */
void prf(uint8_t *out, size_t outlen, const uint8_t key[KYBER_SYMBYTES],
         uint8_t nonce) {
  uint8_t extkey[KYBER_SYMBYTES + 1];

  memcpy(extkey, key, KYBER_SYMBYTES);
  extkey[KYBER_SYMBYTES] = nonce;

  shake256(out, outlen, extkey, KYBER_SYMBYTES + 1);
}

/*
 * Random bytes generation (for testing)
 */
void randombytes(uint8_t *out, size_t outlen) {
  static int initialized = 0;

  if (!initialized) {
    srand(time(NULL)); // Initialize RNG
    initialized = 1;
  }

  for (size_t i = 0; i < outlen; i++) {
    out[i] = rand() & 0xFF;
  }
}

// No wrapper functions for sha3/shake - we use the ones from fips202.c directly
