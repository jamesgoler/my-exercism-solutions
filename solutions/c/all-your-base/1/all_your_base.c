#include "all_your_base.h"

#include <math.h>

static inline size_t digits_to_decimal(int8_t *digits, size_t len, int16_t base);
static inline size_t decimal_to_digits(int8_t *digits, size_t value, int16_t base);

static inline size_t digits_to_decimal(int8_t *digits, size_t len, int16_t base) {
    size_t factor = 1;
    size_t result = 0;
    for (int8_t *ptr = digits + len - 1; ptr >= digits; ptr -= 1) {
        result += factor * *ptr;
        factor *= base;
    }
    return result;
}

static inline size_t decimal_to_digits(int8_t *digits, size_t value, int16_t base) {
    size_t len = 0;
    for (size_t i = value; i > 0; i /= base) {
        len += 1;
    }
    if (len == 0) {
        len = 1;
    }
    for (size_t i = len; i > 0; i -= 1) {
        digits[i-1] = value % base;
        value /= base;
    }
    return len;
}

size_t rebase(int8_t *digits, int16_t input_base, int16_t output_base, size_t input_length) {
    if (input_base <= 1 || output_base <= 1 || input_length == 0) {
        return 0;
    }
    for (size_t i = 0; i < input_length; i += 1) {
        if (digits[i] >= input_base || digits[i] < 0) {
            return 0;
        }
    }
    if (input_base == output_base) {
        return input_length;
    }
    return decimal_to_digits(digits,
                             digits_to_decimal(digits, input_length, input_base),
                             output_base);
}