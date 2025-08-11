#include "sieve.h"

#include <string.h>

uint32_t sieve(uint32_t limit, uint32_t *primes, size_t max_primes) {    
    uint32_t bitmap[(limit + 31) / 32];

    memset(&bitmap, 0, sizeof(bitmap));

    size_t prime_count = 0;
    for (uint32_t i = 2; i <= limit && prime_count < max_primes; i += 1) {
        if (!(bitmap[i / 32] & 1 << (i % 32))) {
            primes[prime_count++] = i;
            for (uint32_t j = i; j <= limit; j += i) {
                bitmap[j / 32] |= 1 << (j % 32);
            }
        }
    }
    return prime_count;
}