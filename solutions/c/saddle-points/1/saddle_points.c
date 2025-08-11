#include "saddle_points.h"

#include <stdio.h>
#include <stdlib.h>

static inline saddle_points_t *new_saddle_points(size_t len);

static inline saddle_points_t *new_saddle_points(size_t len) {
    saddle_points_t *points = malloc(sizeof(saddle_points_t) + len * sizeof(saddle_point_t));
    if (!points) {
        perror("alloc memory for saddle_points_t");
        exit(EXIT_FAILURE);
    }
    points->count = 0;
    return points;
}

saddle_points_t *saddle_points(size_t row_len, size_t col_len, uint8_t matrix[row_len][col_len]) {
    size_t count = 0;

    uint8_t row_maxs[row_len];
    uint8_t col_mins[col_len];
    
    for (size_t r = 0; r < row_len; r += 1) {
        row_maxs[r] = 0;
    }
    for (size_t c = 0; c < col_len; c += 1) {
        col_mins[c] = 255;
    }
    for (size_t r = 0; r < row_len; r += 1) {
        for (size_t c = 0; c < col_len; c += 1) {
            if (row_maxs[r] < matrix[r][c]) {
                row_maxs[r] = matrix[r][c];
            }
            if (col_mins[c] > matrix[r][c]) {
                col_mins[c] = matrix[r][c];
            }
        }
    }
    for (size_t r = 0; r < row_len; r += 1) {
        for (size_t c = 0; c < col_len; c += 1) {
            if (matrix[r][c] == row_maxs[r] && matrix[r][c] == col_mins[c]) {
                count += 1;
            }
        }
    }
    saddle_points_t *result = new_saddle_points(count);

    for (size_t r = 0; r < row_len; r += 1) {
        for (size_t c = 0; c < col_len; c += 1) {
            if (matrix[r][c] == row_maxs[r] && matrix[r][c] == col_mins[c]) {
                result->points[result->count++] = (saddle_point_t) {
                    .row = r + 1,
                    .column = c + 1,
                };
            }
        }
    }
    return result;
}

void free_saddle_points(saddle_points_t *points) {
    free(points);    
}