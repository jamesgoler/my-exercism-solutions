#include "square_root.h"

typedef uint32_t u32;

static inline u32 sqrt_bsearch(u32 n);
static inline u32 sqrt_newton(u32 n);

static inline u32 sqrt_bsearch(u32 n) {
    u32 l = 0;
    u32 r = n + 1;

    while (l < r) {
        u32 m = l + ((r-l) >> 1);
        u32 mm = m * m;
        if (mm == n) {
            return m;
        }
        if (mm < n) {
            l = m + 1;
        } else {
            r = m;
        }
    }
    return l;
}

static inline u32 sqrt_newton(u32 n) {
    u32 m = n;
    while (m*m > n) {
        m = (m + (n / m)) >> 1;
    }
    return m;
}

u32 square_root(u32 n) {
    return sqrt_newton(n);
}