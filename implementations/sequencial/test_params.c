#include "params.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
  printf("Testing Kyber parameters...\n");

  printf("KYBER_K = %d\n", KYBER_K);
  printf("KYBER_N = %d\n", KYBER_N);
  printf("KYBER_Q = %d\n", KYBER_Q);

  printf("KYBER_SYMBYTES = %d\n", KYBER_SYMBYTES);
  printf("KYBER_POLYBYTES = %d\n", KYBER_POLYBYTES);
  printf("KYBER_POLYVECBYTES = %d\n", KYBER_POLYVECBYTES);

  printf("KYBER_PUBLICKEYBYTES = %d\n", KYBER_PUBLICKEYBYTES);
  printf("KYBER_SECRETKEYBYTES = %d\n", KYBER_SECRETKEYBYTES);
  printf("KYBER_CIPHERTEXTBYTES = %d\n", KYBER_CIPHERTEXTBYTES);

  // Test memory allocation and addressing
  printf("Allocating memory...\n");
  uint8_t *pk = malloc(KYBER_PUBLICKEYBYTES);
  uint8_t *sk = malloc(KYBER_SECRETKEYBYTES);

  if (!pk || !sk) {
    printf("Memory allocation failed!\n");
    return 1;
  }

  printf("Memory allocated successfully.\n");
  printf("pk address: %p\n", (void *)pk);
  printf("sk address: %p\n", (void *)sk);
  printf("sk + KYBER_POLYVECBYTES address: %p\n",
         (void *)(sk + KYBER_POLYVECBYTES));

  // Initialize memory
  printf("Initializing memory...\n");
  memset(pk, 0x42, KYBER_PUBLICKEYBYTES);
  memset(sk, 0x43, KYBER_SECRETKEYBYTES);
  printf("Memory initialized.\n");

  // Test memory copy (the operation that might be crashing)
  printf("Testing memcpy operation...\n");
  memcpy(sk + KYBER_POLYVECBYTES, pk, KYBER_PUBLICKEYBYTES);
  printf("memcpy completed successfully.\n");

  // Free memory
  free(pk);
  free(sk);
  printf("Memory freed.\n");

  return 0;
}
