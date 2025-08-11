#include "rational_numbers.h"

#include <stdbool.h>
#include <stdlib.h>
#include <math.h>

static inline rational_t rational(int16_t numerator, int16_t denominator);
static inline rational_t reciprocal(rational_t r);

static inline rational_t rational(int16_t numerator, int16_t denominator) {
    return reduce((rational_t) {
        .numerator = numerator,
        .denominator = denominator,
    });
}

static inline rational_t reciprocal(rational_t r) {
    return rational(r.denominator, r.numerator);
}

rational_t add(rational_t r1, rational_t r2) {
    return reduce(rational(
        r1.numerator * r2.denominator + r2.numerator * r1.denominator,
        r1.denominator * r2.denominator));
}

rational_t subtract(rational_t r1, rational_t r2) {
    return add(r1, rational(-r2.numerator, r2.denominator));
}

rational_t multiply(rational_t r1, rational_t r2) {
    return reduce(rational(
        r1.numerator * r2.numerator,
        r1.denominator * r2.denominator));
}

rational_t divide(rational_t r1, rational_t r2) {
    return multiply(r1, reciprocal(r2));
}

rational_t absolute(rational_t r) {
    return rational(abs(r.numerator), abs(r.denominator));
}

rational_t exp_rational(rational_t r, int16_t n) {
    if (n < 0) {
        r = reciprocal(r);
        n = -n;
    }
    return rational(
        (int16_t)pow(r.numerator, n),
        (int16_t)pow(r.denominator, n));
}

float exp_real(uint16_t x, rational_t r) {
    return powf(x, (float)r.numerator / (float)r.denominator);
}

rational_t reduce(rational_t r) {
    int16_t n = abs(r.denominator);
    for (int16_t i = 2; i <= n; i += 1) {
        while (r.numerator % i == 0 && r.denominator % i == 0) {
            r.numerator /= i;
            r.denominator /= i;
            n /= i;
        }
    }
    if (r.denominator < 0) {
        r.numerator = -r.numerator;
        r.denominator = -r.denominator;
    }
    return r;
}
