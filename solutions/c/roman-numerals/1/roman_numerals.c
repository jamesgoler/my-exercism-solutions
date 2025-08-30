#include "roman_numerals.h"

#include <stdlib.h>
#include <stdbool.h>

static inline bool can_to_roman_numeral(unsigned int number);
static inline size_t estimate_length(unsigned int number);

static inline bool can_to_roman_numeral(unsigned int number) {
    return number > 0 && number <= 3999;
}

static inline size_t estimate_length(unsigned int number) {
    size_t len = 0;
    unsigned int value = 1000;
    while (number > 0) {
        unsigned int d = number / value;
        if (d == 0) {
            value /= 10;
            continue;
        }
        if (d >= 5) {
            d -= 5;
            len += 1;
        }
        if (d == 4) {
            len += 2;
        } else {
            len += d;
        }
        number %= value;
    }
    return len;
}

char *to_roman_numeral(unsigned int number) {
    if (!can_to_roman_numeral(number)) {
        return NULL;
    }
    char *result = malloc(estimate_length(number) + 1);

    char *wptr = result;
    const char *roman_chars = "MDCLXVI";
    const char *ptr = roman_chars;
    unsigned int value = 1000;
    while (number > 0) {
        unsigned int d = number / value;
        if (d == 0) {
            value /= 10;
            ptr += 2;
            continue;
        }
        if (d == 9) {
            *(wptr++) = *ptr;
            *(wptr++) = *(ptr - 2);
        } else if (d == 4) {
            *(wptr++) = *ptr;
            *(wptr++) = *(ptr - 1);
        } else {
            if (d >= 5) {
                d -= 5;
                *(wptr++) = *(ptr - 1);
            }
            for (unsigned int i = 0; i < d; i += 1) {
                *(wptr++) = *ptr;
            }
        }
        number %= value;
    }
    *wptr = '\0';
    return result;
}