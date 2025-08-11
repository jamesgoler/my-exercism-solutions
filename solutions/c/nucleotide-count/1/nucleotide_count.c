#include "nucleotide_count.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

static inline size_t digit_len(size_t n);

static inline size_t digit_len(size_t n) {
    if (n == 0) {
        return 1;
    } else {
        return logl(n) + 1;
    }
}

char *count(const char *dna_strand) {
    size_t a = 0;
    size_t c = 0;
    size_t g = 0;
    size_t t = 0;

    for (const char *ptr = dna_strand; *ptr != '\0'; ptr += 1) {
        switch (*ptr) {
        case 'A':
            a += 1;
            break;
        case 'C':
            c += 1;
            break;
        case 'G':
            g += 1;
            break;
        case 'T':
            t += 1;
            break;
        default:
            return calloc(1, 1);
        }
    }
    
    char *result = malloc(15 + digit_len(a) + digit_len(c) + digit_len(t) + digit_len(g));
    sprintf(result, "A:%ld C:%ld G:%ld T:%ld", a, c, g, t);
    return result;
}
