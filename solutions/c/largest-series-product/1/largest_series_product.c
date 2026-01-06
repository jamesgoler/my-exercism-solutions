#include "largest_series_product.h"
#include <ctype.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>

int64_t largest_series_product(char *digits, size_t span) {
    size_t len = 0;
    for (char *ptr = digits; *ptr != '\0'; ptr += 1) {
        if (!isdigit(*ptr)) {
            return -1;        
        }
        len += 1;
    }
    if (len < span) {
        return -1;
    }
    int64_t max = 0;
    int64_t cur = 1;

    size_t cur_span = 0;
    char *ptr = digits;
    while (*ptr != '\0') {
        while (cur_span < span) {
            if (*ptr == '\0') {
                return max;
            }
            if (*ptr == '0') {
                cur = 1;
                cur_span = 0;
                digits = ptr + 1;
            } else {
                cur *= *ptr - '0';
                cur_span += 1;
            }
            ptr += 1;
        }
        if (cur > max) {
            max = cur;
        }
        cur /= *digits - '0';
        cur_span -= 1;
        digits += 1;
    }
    return max;
}