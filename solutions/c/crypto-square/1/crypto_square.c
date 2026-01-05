#include "crypto_square.h"

#include <string.h>
#include <stdlib.h>
#include <stddef.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>

char *ciphertext(const char *input) {
    if (!input) {
        return NULL;
    }

    size_t len = 0;
    for (const char *rptr = input; *rptr != '\0'; rptr += 1) {
        if (isalnum(*rptr)) {
            len += 1;
        }
    }
    double len_sqrt = sqrt(len);
    size_t cols = ceil(len_sqrt);
    size_t rows = cols * (cols-1) <= len ? cols : cols-1;
    char *result = malloc(sizeof(char) * (rows + 1) * cols); // each row ends with ' ', last row ends with '\0'.
    if (len == 0) {
        result[0] = '\0';
        return result;
    }
    size_t tlen = rows * cols;
    char *tmp = malloc(sizeof(char) * tlen); // each row ends with ' ', last row ends with '\0'.
    char *tptr = tmp;
    for (const char *rptr = input; *rptr != '\0'; rptr += 1) {
        if (isalnum(*rptr)) {
            *(tptr++) = tolower(*rptr);
        }
    }
    printf("%lu", (rows * (cols+1) - 1));
    for (size_t i = len; i < tlen; i += 1) {
        *(tptr++) = ' ';
    }

    char *wptr = result;
    for (size_t j = 0; j < cols; j += 1) {
        for (size_t i = 0; i < rows; i += 1) {
            *(wptr++) = tmp[i * cols + j];
        }
        *(wptr++) = ' ';
    }
    result[(rows+1) * cols - 1] = '\0';
    return result;
}