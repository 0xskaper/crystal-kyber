#ifndef NTT_H

#define NTT_H

#include <stdint.h>

// NTT constants
extern const int16_t zetas[128];
extern const int16_t zetas_inv[128];

// NTT core functions
void ntt(int16_t res[128]);
void invntt_tomont(int16_t res[256]);
void basemul_montgomery(int16_t res[2], const int16_t a[2], const int16_t b[2]);
int16_t montgomery_reduce(int32_t a);
int16_t barrett_reduce(int16_t a);

#endif
