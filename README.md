node-prng - Node bindings of pseudorandom number generators
===

# Background

This project is an assorted Node.js C bindings of some very fast pseudorandom number generators. Most of them is based on [here](http://prng.di.unimi.it/#speed)

# Install

```bash
yarn add node-prng
```

or

```bash
npm install --save node-prng
```

# Usage

```js
const prng = require('node-prng')

console.log(prng.xorshift32().toString('hex')) // 32bit random number
console.log(prng.xorshift64().toString('hex')) // 64bit random number

console.log(prng.xoroshiro128_p().toString('hex')) // 64bit random number, super fast, less "reliable"
console.log(prng.xoroshiro128_pp().toString('hex')) // 64bit random number, fast
console.log(prng.xoroshiro128_ss().toString('hex')) // 64bit random number, very fast

console.log(prng.xoshiro256_p().toString('hex')) // 64bit random number, super fast
console.log(prng.xoshiro256_pp().toString('hex')) // 64bit random number, very fast
console.log(prng.xoshiro256_ss().toString('hex')) // 64bit random number, very fast
```

# Tests

```bash
yarn test
```

or

```bash
npm test
```

# Plan

There is a list of TODO, including more PRNGs, enhancement of the C library and code optimizations. But you might consider in future, we will have:

1. Support for the xoshiro512 family (xoshiro512+, xoshiro512++, xoshiro512**)
2. Support for the xoroshiro1024 family (xoroshiro1024+, xoroshiro1024++, xoroshiro1024**)
3. Larger random bytes array generators using the above.

# Credit

Great thanks to the opened C sources and inspirations by [Sebastiano Vigna](http://vigna.di.unimi.it) of the [Università degli Studi di Milano](http://www.unimi.it/).
