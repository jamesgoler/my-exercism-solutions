#include "diamond.h"
#include <ctype.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>

static inline char *make_diamond_line(size_t row_size, size_t i);

static inline char *make_diamond_line(size_t row_size, size_t i) {
    size_t m = (row_size - 1) >> 1;
    char *line = malloc(sizeof(char) * (row_size + 1));
    if (line) {
        memset(line, ' ', row_size);
        line[m + i] = line[m - i] = i + 'A';
        line[row_size] = '\0';
    }
    return line;
}

char **make_diamond(const char letter) {
    if (!isupper(letter)) {
        return NULL;
    }
    size_t row_size = ((letter - 'A') << 1) + 1;
    char **result = malloc((row_size + 1) * sizeof(char *));
    if (!result) {
        return NULL;
    }
    for (size_t i = 0; i <= row_size; i += 1) {
        result[i] = NULL;
    }
    
    size_t l = 0;
    size_t r = row_size - 1;
    while (l < r) {
        result[l] = make_diamond_line(row_size, l);
        if (!result[l]) {
            free_diamond(result);
            return NULL;
        }
        result[r] = make_diamond_line(row_size, l);
        if (!result[r]) {
            free_diamond(result);
            return NULL;
        }
        l += 1;
        r -= 1;
    }
    result[l] = make_diamond_line(row_size, l);
    if (!result[l]) {
        free_diamond(result);
        return NULL;
    }
    return result;
}

void free_diamond(char **diamond) {
    if (!diamond) {
        return;
    }
    for (size_t i = 0; diamond[i]; i += 1) {
        free(diamond[i]);
        diamond[i] = NULL;
    }
    free(diamond);
}
