#include <common.h>

uint64_t xoshiro256_p_next() {
  const uint64_t result = xp[0] + xp[3];

  const uint64_t t = xp[1] << 17;

  xp[2] ^= xp[0];
  xp[3] ^= xp[1];
  xp[1] ^= xp[2];
  xp[0] ^= xp[3];

  xp[2] ^= t;

  xp[3] = rotl(xp[3], 45);

  return result;
}

uint64_t xoshiro256_pp_next() {
  const uint64_t result = rotl(xpp[0] + xpp[3], 23) + xpp[0];

  const uint64_t t = xpp[1] << 17;

  xpp[2] ^= xpp[0];
  xpp[3] ^= xpp[1];
  xpp[1] ^= xpp[2];
  xpp[0] ^= xpp[3];

  xpp[2] ^= t;

  xpp[3] = rotl(xpp[3], 45);

  return result;
}

uint64_t xoshiro256_ss_next() {
  const uint64_t result = rotl(xss[1] * 5, 7) * 9;

  const uint64_t t = xss[1] << 17;

  xss[2] ^= xss[0];
  xss[3] ^= xss[1];
  xss[1] ^= xss[2];
  xss[0] ^= xss[3];

  xss[2] ^= t;

  xss[3] = rotl(xss[3], 45);

  return result;
}
