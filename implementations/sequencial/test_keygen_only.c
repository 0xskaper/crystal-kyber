#include "kyber.h"
#include "params.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
  printf("Testing keypair generation only\n");

  // Allocate memory
  uint8_t *pk = malloc(KYBER_PUBLICKEYBYTES);
  uint8_t *sk = malloc(KYBER_SECRETKEYBYTES);

  if (!pk || !sk) {
    printf("Memory allocation failed\n");
    return 1;
  }

  // Generate keypair
  printf("Generating keypair...\n");
  int result = crypto_kem_keypair(pk, sk);
  printf("Keypair generation returned: %d\n", result);

  // Free memory
  free(pk);
  free(sk);

  printf("Test completed\n");
  return 0;
}
