// common
#ifndef __COMMON_H__
#define __COMMON_H__

#define NAPI_VERSION 5

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>

static inline uint64_t rotl(const uint64_t x, int k) {
  return (x << k) | (x >> (64 - k));
}

extern uint64_t x; /* The state can be seeded with any value. */

static inline uint64_t splitmix64() {
	uint64_t z = (x += 0x9e3779b97f4a7c15);
	z = (z ^ (z >> 30)) * 0xbf58476d1ce4e5b9;
	z = (z ^ (z >> 27)) * 0x94d049bb133111eb;
	return z ^ (z >> 31);
}

// #define napi_fn(x) napi_value x(napi_env env, napi_callback_info info)
//
// napi_fn(xorshift32);
// napi_fn(xorshift64);
// napi_fn(xoroshiro128_p);
// napi_fn(xoroshiro128_pp);
// napi_fn(xoroshiro128_ss);
// napi_fn(xoshiro256_p);

#define uint64_fn(x) uint64_t x()

uint64_fn(xoroshiro128_p_next);
uint64_fn(xoroshiro128_pp_next);
uint64_fn(xoroshiro128_ss_next);
uint64_fn(xoshiro256_p_next);
uint64_fn(xoshiro256_pp_next);
uint64_fn(xoshiro256_ss_next);

extern uint32_t _seed32;
extern uint64_t _seed64;

extern uint64_t ss[2];
extern uint64_t pp[2];
extern uint64_t p[2];
extern uint64_t xp[4];
extern uint64_t xpp[4];
extern uint64_t xss[4];

#endif
