// debug_kyber.c
#include "ntt.h"
#include "params.h"
#include "poly.h"
#include "polyvec.h"
#include "symmetric.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Test basic functionality
int main(void) {
  srand(time(NULL));
  printf("Initializing test...\n");

  // Test random bytes
  uint8_t rand_buf[32];
  printf("Testing randombytes...\n");
  randombytes(rand_buf, 32);
  printf("Random bytes generated\n");

  // Test SHA3-256
  uint8_t hash[32];
  printf("Testing sha3_256...\n");
  sha3_256(hash, rand_buf, 32);
  printf("SHA3-256 completed\n");

  // Test SHAKE
  uint8_t shake_out[128];
  printf("Testing shake128...\n");
  shake128(shake_out, 128, rand_buf, 32);
  printf("SHAKE128 completed\n");

  // Test polynomial operations
  printf("Testing polynomial operations...\n");
  poly a, b, c;

  // Initialize with random values
  for (int i = 0; i < KYBER_N; i++) {
    a.coeffs[i] = rand() % KYBER_Q;
    b.coeffs[i] = rand() % KYBER_Q;
  }

  // Test addition
  printf("Testing poly_add...\n");
  poly_add(&c, &a, &b);
  printf("Addition completed\n");

  // Test NTT
  printf("Testing poly_ntt...\n");
  poly_ntt(&a);
  printf("NTT completed\n");

  // Test inverse NTT
  printf("Testing poly_invntt_tomont...\n");
  poly_invntt_tomont(&a);
  printf("Inverse NTT completed\n");

  printf("All basic tests passed!\n");
  return 0;
}
