#ifndef NAME_FIX_H
#define NAME_FIX_H

#include "poly.h"
#include "polyvec.h"
#include "symmetric.h"

// Aliases for polynomial functions
#define polynomial_decompress poly_decompress
#define polynomial_getnoise_eta2 poly_getnoise_eta2
#define polynomial_toBytes poly_tobytes
#define polynomial_toMessage poly_tomsg
#define polynomial_tomont poly_tomont

// Aliases for polynomialVector functions
#define polynomialVector_decompress polyvec_decompress
#define polynomialVector_toBytes polyvec_tobytes

// Aliases for missing symmetric functions
#define randomBytes randombytes

#endif
