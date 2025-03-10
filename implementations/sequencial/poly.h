#ifndef POLY_H
#define POLY_H

#include "params.h"
#include <stdint.h>

typedef struct {
  int16_t coeffs[KYBER_N];
} poly;

// Basic polynomial operations
void polynomial_addition(poly *res, const poly *a, const poly *b);
void polynomial_subtraction(poly *res, const poly *a, const poly *b);

// NTT-related functions
void polynomial_ntt(poly *res);
void polynomial_invntt_tomont(poly *res);
void polynomial_basemul_montgomery(poly *res, const poly *a, const poly *b);

// Sampling functions
void polynomial_getnoise_eta1(poly *res, const uint8_t seed[KYBER_SYMBYTES],
                              uint8_t nonce);
void polynomial_getnoise_eta2(poly *res, const uint8_t seed[KYBER_SYMBYTES],
                              uint8_t nonce);
void polynomial_uniform(poly *res, const uint8_t seed[KYBER_SYMBYTES],
                        uint16_t nonce);

// Compression and packing functions
void polynomial_compress(uint8_t *res, const poly *a);
void polynimial_decompress(poly *res, const uint8_t *a);
void polynomial_toBytes(uint8_t *res, const poly *a);
void polynomial_fromBytes(poly *res, const uint8_t *a);
void polynomial_toMessage(uint8_t *res, const poly *a);
void polynomial_fromMessage(poly *res, const uint8_t *a);

// Miscellaneous
void polynomial_reduce(poly *res);
void polynomial_csubq(poly *res);
#endif
