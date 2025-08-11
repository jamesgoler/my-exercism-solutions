#include "prime_factors.h"

#include <stdbool.h>
#include <math.h>

static inline uint64_t next_prime(uint64_t n);
static inline bool is_prime(uint64_t n);

static inline uint64_t next_prime(uint64_t n) {
    do {
        n += 1;
    } while(!is_prime(n));
    return n;
}

static inline bool is_prime(uint64_t n) {
    uint64_t nsqrt = (uint64_t)sqrt(n);
    for (uint64_t i = 2; i < nsqrt; i += 1) {
        if (n % i == 0) {
            return false;
        }
    }
    return true;
}

size_t find_factors(uint64_t n, uint64_t factors[static MAXFACTORS]) {
    size_t count = 0;
    uint64_t i = 2;
    while (n > 1) {
        while (n % i == 0) {
            n /= i;
            factors[count++] = i;
        }
        i = next_prime(i);
    }
    return count;
}