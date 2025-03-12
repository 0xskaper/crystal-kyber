#include "polyvec.h"
#include "params.h"
#include "poly.h"
#include <stdint.h>

/*
 * Add two polynomial vectors
 */
void polyvec_add(polyvec *r, const polyvec *a, const polyvec *b) {
  for (int i = 0; i < KYBER_K; i++) {
    poly_add(&r->vec[i], &a->vec[i], &b->vec[i]);
  }
}

/*
 * Subtract polynomial vector b from a
 */
void polyvec_sub(polyvec *r, const polyvec *a, const polyvec *b) {
  for (int i = 0; i < KYBER_K; i++) {
    poly_sub(&r->vec[i], &a->vec[i], &b->vec[i]);
  }
}

/*
 * Apply NTT to all polynomials in a vector
 */
void polyvec_ntt(polyvec *r) {
  for (int i = 0; i < KYBER_K; i++) {
    poly_ntt(&r->vec[i]);
  }
}

/*
 * Apply inverse NTT to all polynomials in a vector
 */
void polyvec_invntt_tomont(polyvec *r) {
  for (int i = 0; i < KYBER_K; i++) {
    poly_invntt_tomont(&r->vec[i]);
  }
}

/*
 * Pointwise multiply vectors of polynomials, accumulate into a single
 * polynomial
 */
void polyvec_pointwise_acc_montgomery(poly *r, const polyvec *a,
                                      const polyvec *b) {
  poly t;

  poly_basemul_montgomery(r, &a->vec[0], &b->vec[0]);
  for (int i = 1; i < KYBER_K; i++) {
    poly_basemul_montgomery(&t, &a->vec[i], &b->vec[i]);
    poly_add(r, r, &t);
  }
}

/*
 * Convert polynomial vector to byte array
 */
void polyvec_tobytes(uint8_t *r, const polyvec *a) {
  for (int i = 0; i < KYBER_K; i++) {
    poly_tobytes(r + i * KYBER_POLYBYTES, &a->vec[i]);
  }
}

/*
 * Load polynomial vector from byte array
 */
void polyvec_frombytes(polyvec *r, const uint8_t *a) {
  for (int i = 0; i < KYBER_K; i++) {
    poly_frombytes(&r->vec[i], a + i * KYBER_POLYBYTES);
  }
}

/*
 * Compress polynomial vector
 */
void polyvec_compress(uint8_t *r, const polyvec *a) {
  for (int i = 0; i < KYBER_K; i++) {
    // Compress each polynomial to d bits per coefficient
    // For Kyber-768, the compressed size per polynomial is 128 bytes
    poly_compress(r + i * (KYBER_N / 2), &a->vec[i]);
  }
}

/*
 * Decompress polynomial vector
 */
void polyvec_decompress(polyvec *r, const uint8_t *a) {
  for (int i = 0; i < KYBER_K; i++) {
    poly_decompress(&r->vec[i], a + i * (KYBER_N / 2));
  }
}

/*
 * Reduce coefficients of each polynomial in vector
 */
void polyvec_reduce(polyvec *r) {
  for (int i = 0; i < KYBER_K; i++) {
    poly_reduce(&r->vec[i]);
  }
}

/*
 * Conditionally subtract q from each coefficient that is >= q
 */
void polyvec_csubq(polyvec *r) {
  for (int i = 0; i < KYBER_K; i++) {
    poly_csubq(&r->vec[i]);
  }
}
