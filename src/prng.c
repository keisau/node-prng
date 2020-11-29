// Xorshift algorithm for ultra-fast pseudorandom number generator
// https://en.wikipedia.org/wiki/Xorshift
// require NodeJS 12.11.0 or up for NAPI_VERSION 5

#define NAPI_VERSION 5

#include <node_api.h>
#include <common.h>

uint64_t x; /* The state can be seeded with any value. */

uint32_t _seed32;
uint64_t _seed64;

uint64_t ss[2];
uint64_t pp[2];
uint64_t p[2];
uint64_t xp[4];
uint64_t xpp[4];
uint64_t xss[4];

napi_value xorshift32(napi_env env, napi_callback_info info) {
  napi_status status;
  napi_value retval;
  void *buf;
  void *out;

  // xorshift32 algorithm
  uint32_t n = _seed32;

  n ^= n << 13;
  n ^= n >> 17;
  n ^= n << 5;

  _seed32 = n;

  buf = (void*) &n;

  status = napi_create_buffer_copy(env, 4, buf, &out, &retval);
  if (status != napi_ok) {
    return NULL;
  }

  return retval;

}

napi_value xorshift64(napi_env env, napi_callback_info info) {
  napi_status status;
  napi_value retval;
  void *buf;
  void *out;

  // xorshift64 algorithm
  uint64_t n = _seed64;

  n ^= n << 13;
  n ^= n >> 7;
  n ^= n << 17;

  _seed64 = n;

  buf = (void*) &n;

  status = napi_create_buffer_copy(env, 8, buf, &out, &retval);
  if (status != napi_ok) {
    return NULL;
  }

  return retval;
}

napi_value xoroshiro128_ss(napi_env env, napi_callback_info info) {
  napi_status status;
  napi_value retval;
  void *buf;
  void *out;

  uint64_t n = xoroshiro128_ss_next();
  buf = (void*) &n;

  status = napi_create_buffer_copy(env, 8, buf, &out, &retval);
  if (status != napi_ok) {
    return NULL;
  }

  return retval;
}

napi_value xoroshiro128_p(napi_env env, napi_callback_info info) {
  napi_status status;
  napi_value retval;
  void *buf;
  void *out;

  uint64_t n = xoroshiro128_p_next();
  buf = (void*) &n;

  status = napi_create_buffer_copy(env, 8, buf, &out, &retval);
  if (status != napi_ok) {
    return NULL;
  }

  return retval;
}

napi_value xoroshiro128_pp(napi_env env, napi_callback_info info) {
  napi_status status;
  napi_value retval;
  void *buf;
  void *out;

  uint64_t n = xoroshiro128_pp_next();
  buf = (void*) &n;

  status = napi_create_buffer_copy(env, 8, buf, &out, &retval);
  if (status != napi_ok) {
    return NULL;
  }

  return retval;
}

napi_value xoshiro256_p(napi_env env, napi_callback_info info) {
  napi_status status;
  napi_value retval;
  void *buf;
  void *out;

  uint64_t n = xoshiro256_p_next();
  buf = (void*) &n;

  status = napi_create_buffer_copy(env, 8, buf, &out, &retval);
  if (status != napi_ok) {
    return NULL;
  }

  return retval;
}

napi_value xoshiro256_pp(napi_env env, napi_callback_info info) {
  napi_status status;
  napi_value retval;
  void *buf;
  void *out;

  uint64_t n = xoshiro256_pp_next();
  buf = (void*) &n;

  status = napi_create_buffer_copy(env, 8, buf, &out, &retval);
  if (status != napi_ok) {
    return NULL;
  }

  return retval;
}

napi_value xoshiro256_ss(napi_env env, napi_callback_info info) {
  napi_status status;
  napi_value retval;
  void *buf;
  void *out;

  uint64_t n = xoshiro256_ss_next();
  buf = (void*) &n;

  status = napi_create_buffer_copy(env, 8, buf, &out, &retval);
  if (status != napi_ok) {
    return NULL;
  }

  return retval;
}


napi_value init(napi_env env, napi_value exports) {
  napi_status status;
  napi_value fn;

  time_t _t;

  srand((unsigned) time(&_t));

  x = (int) rand();

  _seed32 = (uint32_t)splitmix64();
  _seed64 = splitmix64();
  p[0] = splitmix64();
  p[1] = splitmix64();
  pp[0] = splitmix64();
  pp[1] = splitmix64();
  ss[0] = splitmix64();
  ss[1] = splitmix64();

  for (int i = 0; i < 4; ++i) {
    xp[i] = splitmix64();
    xpp[i] = splitmix64();
    xss[i] = splitmix64();
  }

  // create xorshift32 function
  status = napi_create_function(env, NULL, 0, xorshift32, NULL, &fn);
  if (status != napi_ok) {
    return NULL;
  }

  status = napi_set_named_property(env, exports, "xorshift32", fn);
  if (status != napi_ok) {
    return NULL;
  }

  // create xorshift64 function
  status = napi_create_function(env, NULL, 0, xorshift64, NULL, &fn);
  if (status != napi_ok) {
    return NULL;
  }

  status = napi_set_named_property(env, exports, "xorshift64", fn);
  if (status != napi_ok) {
    return NULL;
  }

  // create xoroshiro128+ function
  status = napi_create_function(env, NULL, 0, xoroshiro128_p, NULL, &fn);
  if (status != napi_ok) {
    return NULL;
  }

  status = napi_set_named_property(env, exports, "xoroshiro128_p", fn);
  if (status != napi_ok) {
    return NULL;
  }

  // create xoroshiro128++ function
  status = napi_create_function(env, NULL, 0, xoroshiro128_pp, NULL, &fn);
  if (status != napi_ok) {
    return NULL;
  }

  status = napi_set_named_property(env, exports, "xoroshiro128_pp", fn);
  if (status != napi_ok) {
    return NULL;
  }

  // create xoroshiro128** function
  status = napi_create_function(env, NULL, 0, xoroshiro128_ss, NULL, &fn);
  if (status != napi_ok) {
    return NULL;
  }

  status = napi_set_named_property(env, exports, "xoroshiro128_ss", fn);
  if (status != napi_ok) {
    return NULL;
  }

  // create xoshiro256+ function
  status = napi_create_function(env, NULL, 0, xoshiro256_p, NULL, &fn);
  if (status != napi_ok) {
    return NULL;
  }

  status = napi_set_named_property(env, exports, "xoshiro256_p", fn);
  if (status != napi_ok) {
    return NULL;
  }

  // create xoshiro256++ function
  status = napi_create_function(env, NULL, 0, xoshiro256_pp, NULL, &fn);
  if (status != napi_ok) {
    return NULL;
  }

  status = napi_set_named_property(env, exports, "xoshiro256_pp", fn);
  if (status != napi_ok) {
    return NULL;
  }

  // create xoshiro256** function
  status = napi_create_function(env, NULL, 0, xoshiro256_ss, NULL, &fn);
  if (status != napi_ok) {
    return NULL;
  }

  status = napi_set_named_property(env, exports, "xoshiro256_ss", fn);
  if (status != napi_ok) {
    return NULL;
  }

  return exports;
}

NAPI_MODULE(NODE_GYP_MODULE_NAME, init)
