#ifndef POLYVEC_H
#define POLYVEC_H

#include "params.h"
#include "poly.h"
#include <stdint.h>

typedef struct {
  poly vec[KYBER_K];
} polyvec;

// Basic vector operations
void polyvec_add(polyvec *r, const polyvec *a, const polyvec *b);
void polyvec_sub(polyvec *r, const polyvec *a, const polyvec *b);

// NTT-related functions
void polyvec_ntt(polyvec *r);
void polyvec_invntt_tomont(polyvec *r);

// Inner product
void polyvec_pointwise_acc_montgomery(poly *r, const polyvec *a,
                                      const polyvec *b);

// Compression and packing functions
void polyvec_compress(uint8_t *r, const polyvec *a);
void polyvec_decompress(polyvec *r, const uint8_t *a);
void polyvec_tobytes(uint8_t *r, const polyvec *a);
void polyvec_frombytes(polyvec *r, const uint8_t *a);

// Miscellaneous
void polyvec_reduce(polyvec *r);
void polyvec_csubq(polyvec *r);

#endif
