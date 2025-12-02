#include "pythagorean_triplet.h"
#include <stdlib.h>
#include <stdint.h>
#include <limits.h>

static inline triplets_t *triplets_new();
static inline int triplets_reserve(triplets_t *triplets, uint16_t n);
static inline int triplets_add_triplet(triplets_t *triplets, triplet_t t);

static inline triplets_t *triplets_new() {
    triplets_t *triplets = malloc(sizeof(triplets_t));
    if (triplets) {
        triplets->triplets = NULL;
        triplets->count = 0;
        triplets->capacity = 0;
    }
    return triplets;
}

static inline int triplets_reserve(triplets_t *triplets, uint16_t n) {
    if (triplets->capacity - triplets->count >= n) {
        return 0;
    }
    if (UINT16_MAX - n < triplets->capacity) {
        return -1;
    }
    triplets->capacity = (triplets->capacity << 1 >= triplets->capacity + n) ? triplets->capacity << 1 : triplets->capacity + n;
    triplets->triplets = realloc(triplets->triplets, triplets->capacity * sizeof(triplet_t));
    if (!triplets->triplets) {
        return -1;
    }
    return 0;
}

static inline int triplets_add_triplet(triplets_t *triplets, triplet_t t) {
    int ret = triplets_reserve(triplets, 1);
    if (ret < 0) {
        return ret;
    }
    triplets->triplets[triplets->count++] = t;
    return 0;
}

triplets_t *triplets_with_sum(uint16_t sum) {
    triplets_t *result = triplets_new();
    if (!result) {
        return result;
    }

    uint16_t one_third = sum / 3;
    uint16_t one_second = sum / 2;
    for (uint16_t a = 1; a <= one_third; a += 1) {
        for (uint16_t b = a + 1; b <= one_second; b += 1) {
            if (sum < a + b) {
                break;
            }
            uint16_t c = sum - a - b;
            if (a * a + b * b == c * c) {
                triplet_t t = (triplet_t) {
                    .a = a,
                    .b = b,
                    .c = c,
                };
                if (triplets_add_triplet(result, t) < 0) {
                    free_triplets(result);
                    return NULL;
                }
            }
        }
    }
    return result;
}

void free_triplets(triplets_t *triplets) {
    if (!triplets) {
        return;
    }
    free(triplets->triplets);
    triplets->triplets = NULL;
    triplets->capacity = 0;
    triplets->count = 0;
    free(triplets);
}