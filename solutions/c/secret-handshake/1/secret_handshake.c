#include "secret_handshake.h"
#include <stdlib.h>

enum command {
    WINK = 1 << 0,
    DOUBLE_BLINK = 1 << 1,
    CLOSE_YOUR_EYES = 1 << 2,
    JUMP = 1 << 3,
    REVERSE = 1 << 4,
};

const size_t COMMAND_NUM = 4;

static inline void swap(const char **a, const char **b);

static inline void swap(const char **a, const char **b) {
    const char *tmp = *a;
    *a = *b;
    *b = tmp;
}

const char **commands(size_t number) {
    const char **result = malloc(COMMAND_NUM * sizeof(char *));
    
    for (size_t i = 0; i < COMMAND_NUM; i += 1) {
        result[i] = NULL;
    }
    
    size_t i = 0;
    if (number & WINK) {
        result[i++] = "wink";
    }
    if (number & DOUBLE_BLINK) {
        result[i++] = "double blink";
    }
    if (number & CLOSE_YOUR_EYES) {
        result[i++] = "close your eyes";
    }
    if (number & JUMP) {
        result[i++] = "jump";
    }
    if (i > 0 && number & REVERSE) {
        i -= 1;
        size_t j = 0;
        while (j < i) {
            swap(&result[i], &result[j]);
            j += 1;
            i -= 1;
        }
    }
    return result;
}
