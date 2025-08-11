#include "pascals_triangle.h"

#include <stdlib.h>

void free_triangle(uint8_t **triangle, size_t rows) {
    if (rows == 0) {
        rows = 1;
    }
    for (size_t i = 0; i < rows; i += 1) {
        free(triangle[i]);
    }
    free(triangle);
}

uint8_t **create_triangle(size_t rows) {
    if (rows == 0) {
        uint8_t **result = malloc(1 * sizeof(uint8_t *));
        result[0] = malloc(1 * sizeof(uint8_t));
        result[0][0] = 0;
        return result;
    }
    uint8_t **result = malloc(rows * sizeof(uint8_t *));
    for (size_t i = 0; i < rows; i += 1) {
        result[i] = malloc(rows * sizeof(uint8_t));
        result[i][0] = 1;
        result[i][i] = 1;
        for (size_t j = 1; j < i; j += 1) {
            result[i][j] = result[i-1][j] + result[i-1][j-1];
        }
        for (size_t j = i + 1; j < rows; j += 1) {
            result[i][j] = 0;
        }
    }
    return result;
}