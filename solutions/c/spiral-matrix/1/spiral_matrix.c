#include "spiral_matrix.h"

#include <stdlib.h>
#include <stdio.h>

static inline void write_one_spiral(int **matrix, int *v, int r, int c, int n);

static inline void write_one_spiral(int **matrix, int *v, int r, int c, int n) {
    for (int i = 0; i < n; i += 1) {
        matrix[r][c++] = (*v)++;
    }
    for (int i = 0; i < n; i += 1) {
        matrix[r++][c] = (*v)++;
    }
    for (int i = 0; i < n; i += 1) {
        matrix[r][c--] = (*v)++;
    }
    for (int i = 0; i < n; i += 1) {
        matrix[r--][c] = (*v)++;
    }
}

spiral_matrix_t *spiral_matrix_create(int size) {
    spiral_matrix_t *result = malloc(sizeof(spiral_matrix_t));
    result->size = size;
    result->matrix = NULL;
    
    if (size == 0) {
        return result;
    }
    
    result->matrix = malloc(sizeof(int *) * size);
    for (int i = 0; i < size; i += 1) {
        result->matrix[i] = malloc(sizeof(int) * size);
    }
    
    int i = 0;
    int j = 0;
    int v = 1;
    for (int s = size - 1; s > 0; s -= 2) {
        write_one_spiral(result->matrix, &v, i, j, s);
        i += 1;
        j += 1;
    }
    if (size % 2 == 1) {
        result->matrix[i][j] = v;
    }
    return result;
}

void spiral_matrix_destroy(spiral_matrix_t *sm) {
    for (int i = 0; i < sm->size; i += 1) {
        free(sm->matrix[i]);
        sm->matrix[i] = NULL;
    }
    free(sm->matrix);
    sm->matrix = NULL;
    free(sm);
}
