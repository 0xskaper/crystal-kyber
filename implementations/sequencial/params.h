#ifndef PARAMS_H
#define PARAMS_H

#define KYBER_K 3 // Kyber-768

#define KYBER_N 256
#define KYBER_Q 3329
#define KYBER_LOGQ 12

// Noise parameters
#define KYBER_ETA1 2
#define KYBER_ETA2 2

// Size of seeds and hashes
#define KYBER_SYMBYTES 32

// Montgomery constants
#define MONT 2285
#define QINV 62209 // -q^-1 mod 2^16

// Size in bytes of polynomial (unpacked)
#define KYBER_POLYBYTES 384

// Size in bytes of polynomial vector (unpacked)
#define KYBER_POLYVECBYTES (KYBER_K * KYBER_POLYBYTES)

// Size in bytes of public key
#define KYBER_PUBLICKEYBYTES (KYBER_POLYVECBYTES + KYBER_SYMBYTES)

// Size in bytes of secret key
#define KYBER_SECRETKEYBYTES                                                   \
  (KYBER_POLYVECBYTES + KYBER_PUBLICKEYBYTES + 2 * KYBER_SYMBYTES)

// Size in bytes of ciphertext
#define KYBER_CIPHERTEXTBYTES (KYBER_POLYVECBYTES + KYBER_POLYBYTES)

// Size in bytes of shared secret
#define KYBER_SSBYTES 32

#define KYBER_POLYBYTES 384
#define KYBER_POLYVECBYTES (KYBER_K * KYBER_POLYBYTES) // Should be 1152
#define KYBER_PUBLICKEYBYTES                                                   \
  (KYBER_POLYVECBYTES + KYBER_SYMBYTES) // Should be 1184
#define KYBER_SECRETKEYBYTES                                                   \
  (KYBER_POLYVECBYTES + KYBER_PUBLICKEYBYTES +                                 \
   2 * KYBER_SYMBYTES) // Should be 2400

// SHAKE/SHA3 rates
#define SHAKE128_RATE 168
#define SHAKE256_RATE 136
#define SHA3_256_RATE 136
#define SHA3_512_RATE 72

#endif
