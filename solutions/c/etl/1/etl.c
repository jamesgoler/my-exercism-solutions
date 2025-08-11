#include "etl.h"

#include <stdlib.h>
#include <string.h>
#include <ctype.h>

static inline size_t legacy_map_size(const legacy_map *input, const size_t input_len);
static int new_map_cmp(const void *a, const void *b);

static inline size_t legacy_map_size(const legacy_map *input, const size_t input_len) {
    int len = 0;
    for (size_t i = 0; i < input_len; i += 1) {
        len += strlen(input[i].keys);
    }
    return len;
}

static int new_map_cmp(const void *a, const void *b) {
    return ((const new_map *)a)->key - ((const new_map *)b)->key;
}

int convert(const legacy_map *input, const size_t input_len, new_map **output) {
    int output_len = legacy_map_size(input, input_len);
    int j = 0;

    new_map *result = malloc(sizeof(new_map) * output_len);
    for (size_t i = 0; i < input_len; i += 1) {
        const legacy_map *m = &input[i];
        for (const char *k = m->keys; *k != '\0'; k += 1) {
            result[j++] = (new_map) {
                .key = tolower(*k),
                .value = m->value,
            };
        }
    }
    qsort(result, output_len, sizeof(new_map), new_map_cmp);
    *output = result;
    return output_len;
}