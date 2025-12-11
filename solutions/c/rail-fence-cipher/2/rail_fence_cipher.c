#include "rail_fence_cipher.h"

#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct walker {
    char *in;
    char *out;
    char *ptr;
};

typedef void (*walk_rails_callback)(size_t i, struct walker *w);

static inline void walk_rails(size_t len, size_t rails, walk_rails_callback callback, struct walker *w);
static void encode_walk(size_t i, struct walker *w);
static void decode_walk(size_t i, struct walker *w);

static inline void walk_rails(size_t len, size_t rails, walk_rails_callback callback, struct walker *w) {
    size_t base_step = (rails - 1) * 2;
    for (size_t r = 0; r < rails; r += 1) {
        size_t step = base_step - (r * 2);
        for (size_t i = r; i < len;) {
            callback(i, w);
            if (step == 0) {
                step = base_step;
                i += step;
            } else {
                i += step;
                step = base_step - step;
            }
        }
    }
}

static void encode_walk(size_t i, struct walker *w) {
    *(w->ptr++) = w->in[i];
}

static void decode_walk(size_t i, struct walker *w) {
    w->out[i] = *(w->ptr++);
}

char *encode(char *text, size_t rails) {
    size_t len = strlen(text);
    char *result = malloc(sizeof(char) * (len + 1));

    struct walker w = (struct walker) {
        .in = text,
        .out = result,
        .ptr = result,
    };

    walk_rails(len, rails, encode_walk, &w);
    result[len] = '\0';
    return result; 
}

char *decode(char *ciphertext, size_t rails) {
    size_t len = strlen(ciphertext);
    char *result = malloc(sizeof(char) * (len + 1));

    struct walker w = (struct walker) {
        .in = ciphertext,
        .out = result,
        .ptr = ciphertext,
    };

    walk_rails(len, rails, decode_walk, &w);

    result[len] = '\0';
    return result;
}
