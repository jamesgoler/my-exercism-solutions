#include "flower_field.h"

#include <string.h>
#include <stdlib.h>
#include <stddef.h>

static inline char count_adjacent(const char **garden, size_t rows, size_t cols, size_t i, size_t j);

static inline char count_adjacent(const char **garden, size_t rows, size_t cols, size_t i, size_t j) {
    size_t l = i == 0      ? 0    : i - 1;
    size_t r = i == rows-1 ? rows : i + 2;
    size_t u = j == 0      ? 0    : j - 1;
    size_t d = j == cols-1 ? cols : j + 2;

    int count = 0;
    for (size_t i = l; i < r; i += 1) {
        for (size_t j = u; j < d; j += 1) {
            if (garden[i][j] == '*') {
                count += 1;
            }
        }
    }
    return count == 0 ? ' ' : '0' + count;
}

char **annotate(const char **garden, const size_t rows) {
    if (!garden || rows == 0) {
        return NULL;
    }

    size_t cols = strlen(garden[0]);
    // declared whole annotation as a string.
    char **result = malloc((rows * (cols+1) * sizeof(char)) + (rows * sizeof(char *)));
     if (!result) {
        return NULL;
    }

    char *garden_rows = (char *)(result + rows);
    char *ptr = garden_rows;

    for (size_t i = 0; i < rows; i += 1) {
        result[i] = ptr;
        for (size_t j = 0; j < cols; j += 1) {
            *(ptr++) = (garden[i][j] == ' ') ? count_adjacent(garden, rows, cols, i, j) : garden[i][j];
        }
        *(ptr++) = '\0';
    }
    return result;
}

void free_annotation(char **annotation) {
    free(annotation);
}
