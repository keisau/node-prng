#include <common.h>

uint64_t xoroshiro128_ss_next() {
  const uint64_t s0 = ss[0];
  uint64_t s1 = ss[1];
  const uint64_t result = rotl(s0 * 5, 7) * 9;

  s1 ^= s0;
  ss[0] = rotl(s0, 24) ^ s1 ^ (s1 << 16); // a, b
  ss[1] = rotl(s1, 37); // c

  return result;
}

uint64_t xoroshiro128_p_next() {
  const uint64_t s0 = p[0];
  uint64_t s1 = p[1];
  const uint64_t result = s0 + s1;

  s1 ^= s0;
  p[0] = rotl(s0, 24) ^ s1 ^ (s1 << 16); // a, b
  p[1] = rotl(s1, 37); // c

  return result;
}

uint64_t xoroshiro128_pp_next() {
  const uint64_t s0 = pp[0];
  uint64_t s1 = pp[1];
  const uint64_t result = rotl(s0 + s1, 17) + s0;

  s1 ^= s0;
  pp[0] = rotl(s0, 49) ^ s1 ^ (s1 << 21); // a, b
  pp[1] = rotl(s1, 28); // c

  return result;
}
