#include "params.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
  printf("Testing basic memory operations\n");

  // Allocate memory
  printf("Allocating memory...\n");
  uint8_t *pk = malloc(KYBER_PUBLICKEYBYTES);
  uint8_t *sk = malloc(KYBER_SECRETKEYBYTES);

  if (!pk || !sk) {
    printf("Memory allocation failed\n");
    return 1;
  }

  // Initialize memory
  printf("Initializing memory...\n");
  memset(pk, 0xAA, KYBER_PUBLICKEYBYTES);
  memset(sk, 0xBB, KYBER_SECRETKEYBYTES);

  // Print first few bytes
  printf("Memory content (pk): %02x %02x %02x %02x\n", pk[0], pk[1], pk[2],
         pk[3]);
  printf("Memory content (sk): %02x %02x %02x %02x\n", sk[0], sk[1], sk[2],
         sk[3]);

  // Free memory WITHOUT calling any other functions
  printf("Freeing memory...\n");
  free(pk);
  free(sk);

  printf("Test completed\n");
  return 0;
}
