#ifndef PARAMS_H
#define PARAMS_H

#define SHAKE128_RATE 168
#define KYBER_K 3
#define KYBER_N 256
#define KYBER_Q 3329

#define KYBER_SYMBYTES 32

#define KYBER_POLYBYTES 384

#define KYBER_POLYVECBYTES (KYBER_K * KYBER_POLYBYTES)

#define KYBER_PUBLICKEYBYTES (KYBER_POLYVECBYTES + KYBER_SYMBYTES)

#define KYBER_SECRETKEYBYTES                                                   \
  (KYBER_POLYVECBYTES + KYBER_PUBLICKEYBYTES + 2 * KYBER_SYMBYTES)

#define KYBER_CIPHERTEXTBYTES (KYBER_POLYVECBYTES + KYBER_POLYBYTES)

#define KYBER_SSBYTES 32

#if KYBER_K == 2 // Kyber-512
#define KYBER_ETA1 3
#elif KYBER_K == 3 // Kyber-768
#define KYBER_ETA1 2
#elif KYBER_K == 4 // Kyber-1024
#define KYBER_ETA1 2
#endif

#define KYBER_ETA2 2 // Same for all parameter sets

#endif
