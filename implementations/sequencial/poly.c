#include "poly.h"
#include "ntt.h"
#include "params.h"
#include "symmetric.h"
#include <stdint.h>

/*
 * Convert a polynomial to Montgomery form
 */
void poly_tomont(poly *r) {
  for (int i = 0; i < KYBER_N; i++) {
    r->coeffs[i] = montgomery_reduce((int32_t)r->coeffs[i] * MONT);
  }
}

void poly_set(poly *r, int16_t value) {
  for (int i = 0; i < KYBER_N; i++) {
    r->coeffs[i] = value;
  }
}

/*
 * Add two polynomials
 */
void poly_add(poly *r, const poly *a, const poly *b) {
  for (int i = 0; i < KYBER_N; i++) {
    r->coeffs[i] = a->coeffs[i] + b->coeffs[i];
  }
}

/*
 * Subtract polynomial b from a
 */
void poly_sub(poly *r, const poly *a, const poly *b) {
  for (int i = 0; i < KYBER_N; i++) {
    r->coeffs[i] = a->coeffs[i] - b->coeffs[i];
  }
}

/*
 * Apply forward NTT transformation to a polynomial
 */
void poly_ntt(poly *r) { ntt(r->coeffs); }

/*
 * Apply inverse NTT transformation to a polynomial and multiply by Montgomery
 * factor
 */
void poly_invntt_tomont(poly *r) { invntt_tomont(r->coeffs); }

/*
 * Polynomial multiplication in NTT domain
 */
void poly_basemul_montgomery(poly *r, const poly *a, const poly *b) {
  for (int i = 0; i < KYBER_N / 2; i++) {
    basemul_montgomery(&r->coeffs[2 * i], &a->coeffs[2 * i], &b->coeffs[2 * i]);
  }
}

/*
 * Generate a polynomial with uniformly random coefficients in [0, q-1]
 */
void poly_uniform(poly *r, const uint8_t seed[KYBER_SYMBYTES], uint16_t nonce) {
  uint8_t buf[SHAKE128_RATE * 2];
  xof_state state;

  xof_absorb(&state, seed, nonce & 0xFF, nonce >> 8);
  xof_squeezeblocks(buf, 2, &state);

  uint16_t val;
  size_t ctr = 0;

  for (int i = 0; i < KYBER_N; i++) {
    do {
      if (ctr >= SHAKE128_RATE * 2) {
        xof_squeezeblocks(buf, 1, &state);
        ctr = 0;
      }

      val = ((buf[ctr] | ((uint16_t)buf[ctr + 1] << 8)) & 0x0FFF);
      ctr += 2;
    } while (val >= KYBER_Q);

    r->coeffs[i] = val;
  }

  xof_ctx_release(&state);
}

/*
 * Generate a polynomial with small noise using η₁
 */
void poly_getnoise_eta1(poly *r, const uint8_t seed[KYBER_SYMBYTES],
                        uint8_t nonce) {
  uint8_t buf[KYBER_ETA1 * KYBER_N / 4];
  prf(buf, sizeof(buf), seed, nonce);

  for (int i = 0; i < KYBER_N / 4; i++) {
    uint8_t t0 = buf[i] & 0x03;
    uint8_t t1 = (buf[i] >> 2) & 0x03;
    uint8_t t2 = (buf[i] >> 4) & 0x03;
    uint8_t t3 = (buf[i] >> 6) & 0x03;

    r->coeffs[4 * i + 0] = KYBER_ETA1 - t0;
    r->coeffs[4 * i + 1] = KYBER_ETA1 - t1;
    r->coeffs[4 * i + 2] = KYBER_ETA1 - t2;
    r->coeffs[4 * i + 3] = KYBER_ETA1 - t3;
  }
}

/*
 * Generate a polynomial with small noise using η₂
 */
void poly_getnoise_eta2(poly *r, const uint8_t seed[KYBER_SYMBYTES],
                        uint8_t nonce) {
  uint8_t buf[KYBER_ETA2 * KYBER_N / 4];
  prf(buf, sizeof(buf), seed, nonce);

  for (int i = 0; i < KYBER_N / 4; i++) {
    uint8_t t0 = buf[i] & 0x03;
    uint8_t t1 = (buf[i] >> 2) & 0x03;
    uint8_t t2 = (buf[i] >> 4) & 0x03;
    uint8_t t3 = (buf[i] >> 6) & 0x03;

    r->coeffs[4 * i + 0] = KYBER_ETA2 - t0;
    r->coeffs[4 * i + 1] = KYBER_ETA2 - t1;
    r->coeffs[4 * i + 2] = KYBER_ETA2 - t2;
    r->coeffs[4 * i + 3] = KYBER_ETA2 - t3;
  }
}

/*
 * Convert polynomial to bytes. Results in compressed representation
 */
void poly_tobytes(uint8_t *r, const poly *a) {
  uint16_t t[8];

  for (int i = 0; i < KYBER_N / 8; i++) {
    for (int j = 0; j < 8; j++) {
      t[j] = a->coeffs[8 * i + j];
      t[j] += (t[j] >> 15) & KYBER_Q; // If negative, add q
    }

    r[0] = t[0] & 0xff;
    r[1] = (t[0] >> 8) | ((t[1] & 0x1f) << 3);
    r[2] = (t[1] >> 5) | ((t[2] & 0x03) << 6);
    r[3] = (t[2] >> 2) & 0xff;
    r[4] = (t[2] >> 10) | ((t[3] & 0x7f) << 1);
    r[5] = (t[3] >> 7) | ((t[4] & 0x0f) << 4);
    r[6] = (t[4] >> 4) | ((t[5] & 0x01) << 7);
    r[7] = (t[5] >> 1) & 0xff;
    r[8] = (t[5] >> 9) | ((t[6] & 0x3f) << 2);
    r[9] = (t[6] >> 6) | ((t[7] & 0x07) << 5);
    r[10] = (t[7] >> 3);

    r += 11;
  }
}

/*
 * Convert bytes to polynomial
 */
void poly_frombytes(poly *r, const uint8_t *a) {
  for (int i = 0; i < KYBER_N / 8; i++) {
    r->coeffs[8 * i + 0] = a[0] | ((uint16_t)(a[1] & 0x07) << 8);
    r->coeffs[8 * i + 1] = (a[1] >> 3) | ((uint16_t)(a[2] & 0x3f) << 5);
    r->coeffs[8 * i + 2] =
        (a[2] >> 6) | ((uint16_t)(a[3]) << 2) | ((uint16_t)(a[4] & 0x01) << 10);
    r->coeffs[8 * i + 3] = (a[4] >> 1) | ((uint16_t)(a[5] & 0x0f) << 7);
    r->coeffs[8 * i + 4] = (a[5] >> 4) | ((uint16_t)(a[6] & 0x7f) << 4);
    r->coeffs[8 * i + 5] =
        (a[6] >> 7) | ((uint16_t)(a[7]) << 1) | ((uint16_t)(a[8] & 0x03) << 9);
    r->coeffs[8 * i + 6] = (a[8] >> 2) | ((uint16_t)(a[9] & 0x1f) << 6);
    r->coeffs[8 * i + 7] = (a[9] >> 5) | ((uint16_t)(a[10]) << 3);

    a += 11;
  }
}

/*
 * Convert message to polynomial
 */
void poly_frommsg(poly *r, const uint8_t *msg) {
  for (int i = 0; i < KYBER_N / 8; i++) {
    for (int j = 0; j < 8; j++) {
      // Map bits 0 and 1 to 0 and q/2
      r->coeffs[8 * i + j] = ((msg[i] >> j) & 1) * (KYBER_Q / 2);
    }
  }
}

/*
 * Convert polynomial to message
 */
void poly_tomsg(uint8_t *msg, const poly *a) {
  uint16_t t;

  for (int i = 0; i < KYBER_N / 8; i++) {
    msg[i] = 0;
    for (int j = 0; j < 8; j++) {
      t = a->coeffs[8 * i + j];
      t += ((int16_t)t >> 15) & KYBER_Q; // If negative, add q

      // Compress to a single bit (0 or 1)
      msg[i] |= ((t + KYBER_Q / 4) >> (KYBER_LOGQ - 1)) << j;
    }
  }
}

/*
 * Compress polynomial to byte array
 */
void poly_compress(uint8_t *r, const poly *a) {
  uint32_t t[8];

  for (int i = 0; i < KYBER_N / 8; i++) {
    for (int j = 0; j < 8; j++) {
      // Map from [0, q-1] to [0, 2^d-1] (d=4 for Kyber-768)
      t[j] = ((((uint32_t)a->coeffs[8 * i + j] << 4) + KYBER_Q / 2) / KYBER_Q) &
             15;
    }

    r[0] = t[0] | (t[1] << 4);
    r[1] = t[2] | (t[3] << 4);
    r[2] = t[4] | (t[5] << 4);
    r[3] = t[6] | (t[7] << 4);

    r += 4;
  }
}

/*
 * Decompress byte array to polynomial
 */
void poly_decompress(poly *r, const uint8_t *a) {
  for (int i = 0; i < KYBER_N / 2; i++) {
    r->coeffs[2 * i + 0] = (((uint16_t)(a[i] & 15) * KYBER_Q) + 8) >> 4;
    r->coeffs[2 * i + 1] = (((uint16_t)(a[i] >> 4) * KYBER_Q) + 8) >> 4;
  }
}

/*
 * Reduce all coefficients to the standard representative
 */
void poly_reduce(poly *r) {
  for (int i = 0; i < KYBER_N; i++) {
    r->coeffs[i] = barrett_reduce(r->coeffs[i]);
  }
}

/*
 * Conditionally subtract q from each coefficient that is >= q
 */
void poly_csubq(poly *r) {
  for (int i = 0; i < KYBER_N; i++) {
    r->coeffs[i] -= KYBER_Q & ((r->coeffs[i] - KYBER_Q) >> 15);
  }
}
