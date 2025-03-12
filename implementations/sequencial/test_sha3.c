#include "fips202.h"
#include "params.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
  printf("Testing SHA3 operations\n");

  // Allocate memory
  uint8_t input[32];
  uint8_t output[32];

  // Initialize input
  memset(input, 0x42, sizeof(input));

  // Perform SHA3-256
  printf("Calling sha3_256...\n");
  sha3_256(output, input, sizeof(input));
  printf("SHA3-256 completed\n");

  // Print output
  printf("SHA3-256 output: %02x %02x %02x %02x\n", output[0], output[1],
         output[2], output[3]);

  printf("Test completed\n");
  return 0;
}
