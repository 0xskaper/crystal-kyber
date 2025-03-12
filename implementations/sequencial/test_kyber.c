#include "kyber.h"
#include "params.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main(void) {
  // Initialize random number generator
  srand(time(NULL));

  uint8_t pk[KYBER_PUBLICKEYBYTES];
  uint8_t sk[KYBER_SECRETKEYBYTES];
  uint8_t ct[KYBER_CIPHERTEXTBYTES];
  uint8_t ss_a[KYBER_SSBYTES];
  uint8_t ss_b[KYBER_SSBYTES];

  printf("Testing CRYSTALS-Kyber (K=%d)...\n\n", KYBER_K);

  printf("Generating keypair...\n");
  if (crypto_kem_keypair(pk, sk) != 0) {
    printf("Keypair generation failed!\n");
    return 1;
  }

  printf("Public key (first 16 bytes): ");
  for (int i = 0; i < 16; i++) {
    printf("%02x", pk[i]);
  }
  printf("...\n\n");

  printf("Encapsulating shared secret...\n");
  if (crypto_kem_enc(ct, ss_a, pk) != 0) {
    printf("Encapsulation failed!\n");
    return 1;
  }

  printf("Decapsulating shared secret...\n");
  if (crypto_kem_dec(ss_b, ct, sk) != 0) {
    printf("Decapsulation failed!\n");
    return 1;
  }

  printf("Shared secret from encapsulation: ");
  for (int i = 0; i < KYBER_SSBYTES; i++) {
    printf("%02x", ss_a[i]);
  }
  printf("\n");

  printf("Shared secret from decapsulation: ");
  for (int i = 0; i < KYBER_SSBYTES; i++) {
    printf("%02x", ss_b[i]);
  }
  printf("\n\n");

  if (memcmp(ss_a, ss_b, KYBER_SSBYTES) == 0) {
    printf("SUCCESS: Shared secrets match!\n");
    return 0;
  } else {
    printf("ERROR: Shared secrets do not match!\n");
    return 1;
  }
}
