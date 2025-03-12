#include "ntt.h"
#include "params.h"
#include <stdint.h>

// Precomputed NTT constants (twiddle factors)
const int16_t zetas[128] = {
    2285, 2571, 2970, 1812, 1493, 1422, 287,  202,  3158, 622,  1577, 182,
    962,  2127, 1855, 1468, 573,  2004, 264,  383,  2500, 1458, 1727, 3199,
    2648, 1017, 732,  608,  1787, 411,  3124, 1758, 1223, 652,  2777, 1015,
    2036, 1491, 3047, 1785, 516,  3321, 3009, 2663, 1711, 2167, 126,  1469,
    2476, 3239, 3058, 830,  107,  1908, 3082, 2378, 2931, 961,  1821, 2604,
    448,  2264, 677,  2054, 2226, 430,  555,  843,  2078, 871,  1550, 105,
    422,  587,  177,  3094, 3038, 2869, 1574, 1653, 3083, 778,  1159, 3182,
    2552, 1483, 2727, 1119, 1739, 644,  2457, 349,  418,  329,  3173, 3254,
    817,  1097, 603,  610,  1322, 2044, 1864, 384,  2114, 3193, 1218, 1994,
    2455, 220,  2142, 1670, 2144, 1799, 2051, 794,  1819, 2475, 2459, 478,
    3221, 3021, 996,  991,  958,  1869, 1522, 1628};

const int16_t zetas_inv[128] = {
    1701, 1807, 1460, 2371, 2338, 2333, 308,  108,  2851, 870,  854,  1510,
    2535, 1278, 1530, 1185, 1659, 1187, 3109, 874,  1335, 2111, 136,  1215,
    2945, 1465, 1285, 2007, 2719, 2726, 2232, 2512, 75,   156,  3000, 2911,
    2980, 872,  2685, 1590, 2210, 602,  1846, 777,  147,  2170, 2551, 246,
    1676, 1755, 460,  291,  235,  3152, 2742, 2907, 3224, 1779, 2458, 1251,
    2486, 2933, 1106, 2040, 1393, 1581, 1633, 1764, 2323, 3007, 1031, 2933,
    1769, 901,  1983, 1830, 1802, 1214, 716,  2490, 950,  2618, 1328, 2018,
    1525, 2738, 2310, 2245, 1471, 2434, 718,  1893, 1372, 2163, 2168, 2311,
    1636, 1138, 2454, 940,  317,  1196, 342,  1257, 2918, 324,  2158, 1616,
    2736, 1345, 2596, 1175, 112,  2682, 2147, 3049, 2006, 1487, 485,  5,
    152,  1752, 2219, 2415, 2385, 2979, 2388, 1356};

/*
 * Montgomery reduction
 * Input: a <= 2^31 * q
 * Output: r congruent to a * 2^-16 mod q, with r < 2*q
 */
int16_t montgomery_reduce(int32_t a) {
  int32_t t;
  int16_t u;

  u = a * QINV;
  u &= 0xFFFF;
  t = u * KYBER_Q;
  t = a - t;
  t >>= 16;

  return t;
}

/*
 * Barrett reduction
 * Input: a < 2^14 * q
 * Output: r congruent to a mod q, with r < 2*q
 */
int16_t barrett_reduce(int16_t a) {
  int16_t t;
  const int16_t v = ((1 << 26) + KYBER_Q / 2) / KYBER_Q; // v = 2^26/q + 1/2

  t = ((int32_t)v * a + (1 << 25)) >> 26; // t = floor(v*a + 2^25)/2^26
  t *= KYBER_Q;

  return a - t;
}

/*
 * Forward NTT transform
 */
void ntt(int16_t r[256]) {
  int16_t t, zeta;
  int j, k = 1;

  // The NTT algorithm (Cooley-Tukey butterfly pattern)
  for (int len = 128; len >= 2; len >>= 1) {
    for (int start = 0; start < 256; start = j + len) {
      zeta = zetas[k++];
      for (j = start; j < start + len; j++) {
        t = montgomery_reduce((int32_t)zeta * r[j + len]);
        r[j + len] = r[j] - t;
        r[j] = r[j] + t;
      }
    }
  }
}

/*
 * Inverse NTT transform and multiplication by Montgomery factor 2^16
 */
void invntt_tomont(int16_t r[256]) {
  int16_t t, zeta;
  int j, k = 127;

  // The inverse NTT algorithm (Gentleman-Sande butterfly pattern)
  for (int len = 2; len <= 128; len <<= 1) {
    for (int start = 0; start < 256; start = j + len) {
      zeta = zetas_inv[k--];
      for (j = start; j < start + len / 2; j++) {
        t = r[j];
        r[j] = barrett_reduce(t + r[j + len / 2]);
        r[j + len / 2] = t - r[j + len / 2];
        r[j + len / 2] = montgomery_reduce((int32_t)zeta * r[j + len / 2]);
      }
    }
  }

  // Multiply by Montgomery factor 2^16/n
  for (j = 0; j < 256; j++) {
    r[j] = montgomery_reduce((int32_t)r[j] * 1441); // 1441 = 2^16/256 mod q
  }
}

/*
 * Multiplication of two elements in Z_q[X]/(X^2-zeta)
 */
void basemul_montgomery(int16_t r[2], const int16_t a[2], const int16_t b[2]) {
  int16_t zeta = zetas[64]; // Special value for X^2 = zeta

  r[0] = montgomery_reduce((int32_t)a[0] * b[0]);
  r[0] += montgomery_reduce((int32_t)a[1] * b[1] * zeta);
  r[1] = montgomery_reduce((int32_t)a[0] * b[1]);
  r[1] += montgomery_reduce((int32_t)a[1] * b[0]);
}
