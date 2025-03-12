#ifndef POLY_H
#define POLY_H

#include "params.h"
#include <stdint.h>

typedef struct {
  int16_t coeffs[KYBER_N];
} poly;

// Basic polynomial operations
void poly_add(poly *r, const poly *a, const poly *b);
void poly_sub(poly *r, const poly *a, const poly *b);
// Add to poly.h
void poly_set(poly *r, int16_t value);

// Add to poly.c

// NTT-related functions
void poly_ntt(poly *r);
void poly_invntt_tomont(poly *r);
void poly_basemul_montgomery(poly *r, const poly *a, const poly *b);
void poly_tomont(poly *r);

// Sampling functions
void poly_getnoise_eta1(poly *r, const uint8_t seed[KYBER_SYMBYTES],
                        uint8_t nonce);
void poly_getnoise_eta2(poly *r, const uint8_t seed[KYBER_SYMBYTES],
                        uint8_t nonce);
void poly_uniform(poly *r, const uint8_t seed[KYBER_SYMBYTES], uint16_t nonce);

// Compression and packing functions
void poly_compress(uint8_t *r, const poly *a);
void poly_decompress(poly *r, const uint8_t *a);
void poly_tobytes(uint8_t *r, const poly *a);
void poly_frombytes(poly *r, const uint8_t *a);
void poly_tomsg(uint8_t *r, const poly *a);
void poly_frommsg(poly *r, const uint8_t *a);

// Miscellaneous
void poly_reduce(poly *r);
void poly_csubq(poly *r);

#endif
