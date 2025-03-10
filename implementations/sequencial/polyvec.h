#ifndef POLYVEC_H
#define POLYVEC_H

#include "params.h"
#include "poly.h"
#include <stdint.h>

typedef struct {
  poly vec[KYBER_N];
} polyvec;

// Basic vector operations
void polynomialVector_addition(polyvec *res, const polyvec *a,
                               const polyvec *b);
void polynomialVector_subtraction(polyvec *res, const polyvec *a,
                                  const polyvec *b);

// NTT-related functions
void polynomialVector_ntt(polyvec *res);
void polynomial_invtt_tomont(polyvec *res);

// Inner product
void polynomialVector_pointwise_acc_montgomery(poly *res, const polyvec *a,
                                               const polyvec *b);

// Compression and packing functions
void polynomialVector_compress(uint8_t *res, const polyvec *a);
void polynomialVector_decompress(polyvec *res, const uint8_t *a);
void polynomialVector_toBytes(uint8_t *res, const polyvec *a);
void polynomialVector_fromBytes(polyvec *res, const uint8_t *a);

// Miscellaneous
void polynomialVector_reduce(polyvec *res);
void polynomialVector_csubq(polyvec *res);

#endif
