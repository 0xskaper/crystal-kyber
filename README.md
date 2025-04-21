# Kyber Post-Quantum Cryptography Implementation
## Computational Mathematics Project
### Submitted to Professor Curtis Bright, University of Windsor

This repository contains an implementation of the Kyber post-quantum key encapsulation mechanism (KEM). Kyber is a lattice-based cryptographic algorithm selected by NIST as a standard for post-quantum cryptography.

## Overview

CRYSTALS-Kyber (Kyber) is a module lattice-based key encapsulation mechanism designed to be secure against attacks from both classical and quantum computers. It's part of the NIST Post-Quantum Cryptography Standardization process and has been selected as a standard for post-quantum key establishment.

## Features

- Implementation of Kyber key generation, encapsulation, and decapsulation
- Test suite to verify correctness
- Optimized Number Theoretic Transform (NTT) implementation
- FIPS-202 compliant SHA-3/SHAKE implementations

## Requirements

- GCC or compatible C compiler
- GNU Make

## Building

To build the project, simply run:

```
make
```

This will compile all source files and create the `test_kyber` executable.

## Testing

To run the test suite:

```
make run
```

Or manually after building:

```
./test_kyber
```

## Cleaning

To clean all compiled files:

```
make clean
```

## Project Structure

- `kyber.c/h`: Main Kyber algorithm implementation
- `poly.c/h`: Polynomial operations
- `polyvec.c/h`: Vector of polynomials operations
- `ntt.c/h`: Number Theoretic Transform implementation
- `fips202.c/h`: SHA-3/SHAKE implementations
- `symmetric.c/h`: Symmetric primitives wrapper
- `test_kyber.c`: Test suite for Kyber

## Security Parameters

Kyber comes in three variants with different security levels:

- **Kyber-512**: Equivalent to AES-128 security level
- **Kyber-768**: Equivalent to AES-192 security level
- **Kyber-1024**: Equivalent to AES-256 security level

## Usage

The implementation provides the following main functions:

```c
// Key generation
int crypto_kem_keypair(unsigned char *pk, unsigned char *sk);

// Encapsulation
int crypto_kem_enc(unsigned char *ct, unsigned char *ss, const unsigned char *pk);

// Decapsulation
int crypto_kem_dec(unsigned char *ss, const unsigned char *ct, const unsigned char *sk);
```

## License

[Your license information here]

## References

1. CRYSTALS-Kyber Algorithm Specifications: https://pq-crystals.org/kyber/
2. NIST Post-Quantum Cryptography Standardization: https://csrc.nist.gov/projects/post-quantum-cryptography
