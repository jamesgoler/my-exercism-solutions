#include "binary_search.h"

const int *binary_search(int value, const int *arr, size_t length) {
    const int *l = arr;
    const int *r = arr + length;

    while (l < r) {
        const int *m = l + ((r - l) >> 1);
        if (*m == value) {
            return m;
        }
        if (*m > value) {
            r = m;
        } else {
            l = m + 1;
        }
    }
    return NULL;
}