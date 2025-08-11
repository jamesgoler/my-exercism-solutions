#include "hamming.h"

#include <string.h>


int compute(const char *lhs, const char *rhs) {
    int diff = 0;
    while (*lhs != '\0' && *rhs != '\0') {
        if (*lhs++ != *rhs++) {
            diff += 1;
        }
    }
    if (*lhs != *rhs) {
        return -1;
    }
    return diff;
}