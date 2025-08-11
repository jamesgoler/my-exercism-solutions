#include "nth_prime.h"

#include <math.h>
#include <stdbool.h>

static inline uint32_t next_prime(uint32_t n);
static inline bool is_prime(uint32_t n);

static inline uint32_t next_prime(uint32_t n) {
    do {
        n += 1;  
    } while (!is_prime(n));
    return n;
}

static inline bool is_prime(uint32_t n) {
    uint32_t nsqrt = (uint32_t)sqrt(n);
    for (uint32_t i = 2; i <= nsqrt; i += 1) {
        if (n % i == 0) {
            return false;
        }
    }
    return true;
}

uint32_t nth(uint32_t n) {
    if (n == 0) {
        return 0;
    }
    uint32_t current = 2;
    for (uint32_t i = 1; i < n; i += 1) {
        current = next_prime(current);
    }
    return current;
}