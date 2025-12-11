#include "rail_fence_cipher.h"
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char *encode(char *text, size_t rails) {
    size_t len = strlen(text);
    char *result = malloc(sizeof(char) * (len + 1));
    char *wptr = result;

    size_t base_step = (rails - 1) * 2;
    for (size_t r = 0; r < rails; r += 1) {
        size_t step = base_step - (r * 2);
        for (size_t i = r; i < len;) {
            *(wptr++) = text[i];
            if (step == 0) {
                step = base_step;
                i += step;
            } else {
                i += step;
                step = base_step - step;
            }
        }
    }
    result[len] = '\0';
    return result;
}

char *decode(char *ciphertext, size_t rails) {
    size_t len = strlen(ciphertext);
    char *result = malloc(sizeof(char) * (len + 1));

    size_t j = 0;
    size_t base_step = (rails - 1) * 2;
    for (size_t r = 0; r < rails; r += 1) {
        size_t step = base_step - (r * 2);
        for (size_t i = r; i < len;) {
            result[i] = ciphertext[j++];
            if (step == 0) {
                step = base_step;
                i += step;
            } else {
                i += step;
                step = base_step - step;
            }
        }
    }
    result[len] = '\0';
    return result;
}
