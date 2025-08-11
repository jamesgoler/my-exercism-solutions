#include "prime_factors.h"

size_t find_factors(uint64_t n, uint64_t factors[static MAXFACTORS]) {
    size_t count = 0;
    uint64_t i = 2;
    while (n > 1) {
        while (n % i == 0) {
            n /= i;
            factors[count++] = i;
        }
        i += 1;
    }
    return count;
}