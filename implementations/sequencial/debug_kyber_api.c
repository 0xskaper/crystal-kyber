#include "kyber.h"
#include "params.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main(void) {
  // Initialize random number generator
  srand(time(NULL));

  printf("Testing simplified CRYSTALS-Kyber API\n\n");

  // Allocate memory for keys, ciphertext, and shared secrets
  uint8_t *pk = malloc(KYBER_PUBLICKEYBYTES);
  uint8_t *sk = malloc(KYBER_SECRETKEYBYTES);
  uint8_t *ct = malloc(KYBER_CIPHERTEXTBYTES);
  uint8_t *ss_a = malloc(KYBER_SSBYTES);
  uint8_t *ss_b = malloc(KYBER_SSBYTES);

  if (!pk || !sk || !ct || !ss_a || !ss_b) {
    printf("Memory allocation failed\n");
    return 1;
  }

  printf("Memory allocated successfully\n");

  // Generate keypair
  printf("Generating keypair...\n");
  if (crypto_kem_keypair(pk, sk) != 0) {
    printf("Keypair generation failed!\n");
    return 1;
  }

  // Encapsulation
  printf("Encapsulating shared secret...\n");
  if (crypto_kem_enc(ct, ss_a, pk) != 0) {
    printf("Encapsulation failed!\n");
    return 1;
  }

  // Decapsulation
  printf("Decapsulating shared secret...\n");
  if (crypto_kem_dec(ss_b, ct, sk) != 0) {
    printf("Decapsulation failed!\n");
    return 1;
  }

  // Check if the shared secrets match
  if (memcmp(ss_a, ss_b, KYBER_SSBYTES) != 0) {
    printf("ERROR: Shared secrets do not match!\n");
  } else {
    printf("SUCCESS: Shared secrets match!\n");
  }

  // Free memory
  free(pk);
  free(sk);
  free(ct);
  free(ss_a);
  free(ss_b);

  printf("Test completed and memory freed\n");
  return 0;
}
