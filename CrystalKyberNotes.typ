= CRYSTAL-Kyber: _A Post-Quantum Key Encapsulation Mechanism_
== Overview
CRYSTALS-Kyber is a lattice-based key encapsulation mechanism (KEM) selected by NIST as a post-quantum cryptography standard. It's designed to be secure against attacks from both classical and quantum computers.
- *Key Feature:* 
  + Based on the Module Learning With Error (MLWE) Problem.
  + Available in three security levels: Kyber-512, Kyber-768, and Kyber-1024
  + Offers a good balance between security, performance, and key/ciphertext size

== Mathematical Foundation
=== Polynomial Ring
Kyber operates in the polynomial ring $R = Z_q[X]/(X^n+1)$ where: 
  + $n = 256$ (polynomial degree)
  + $q = 3329$ (modulus, a prime number)

All operations on polynomials are performed modulo $X^n+1$ and coefficient-wise modulo $q$.

=== Module-LWE Problem
The security of Kyber relies on the hardness of the Module-LWE problem, which is generalization of the Learning with Errors (LWE) problem to module lattices.

== Number Theoretic Transform (NTT) 
The NTT is used for efficient polynomial multiplication, similar to how FFT works but in a finite field.
