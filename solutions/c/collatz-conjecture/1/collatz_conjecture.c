#include "collatz_conjecture.h"

int steps(int start) {
    if (start <= 0) {
        return ERROR_VALUE;
    }
    int s;
    for (s = 0; start != 1; s += 1) {
        if (start & 1) {
            start = (start << 1) + start + 1;
        } else {
            start >>= 1;
        }
    }
    return s;
}
