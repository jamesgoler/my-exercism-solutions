#include "series.h"
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

static inline void init_slices(slices_t *slices, unsigned int count);
static inline void free_slices(slices_t *slices);

static inline void init_slices(slices_t *slices, unsigned int count) {
    slices->substring_count = count;
    if (count > 0) {
        slices->substring = malloc(sizeof(char *) * count);
        if (!slices->substring) {
            free_slices(slices);
        }
        for (unsigned int i = 0; i < slices->substring_count; i += 1) {
            slices->substring[i] = NULL;
        }
    } else {
        slices->substring = NULL;
    }
}

static inline void free_slices(slices_t *slices) {
    if (slices->substring) {
        for (unsigned int i = 0; i < slices->substring_count; i += 1) {
            free(slices->substring[i]);
            slices->substring[i] = NULL;
        }
        free(slices->substring);
    }
    init_slices(slices, 0);
}

slices_t slices(char *input_text, unsigned int substring_length) {
    size_t len = 0;
    if (input_text) {
        len = strlen(input_text);
    }
    slices_t result;
    init_slices(&result, 0);

    if (len >= substring_length && substring_length > 0) {
        init_slices(&result, len - substring_length + 1);
        for (unsigned int i = 0; i < result.substring_count; i += 1) {
            result.substring[i] = malloc(sizeof(*result.substring[i]) * substring_length + 1);
            if (!result.substring[i]) {
                free_slices(&result);
                return result;
            }
            strncpy(result.substring[i], input_text + i, substring_length);
            result.substring[i][substring_length] = '\0';
        }
    }
    return result;
}
