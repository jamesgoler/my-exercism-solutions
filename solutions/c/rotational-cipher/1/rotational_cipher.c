#include "rotational_cipher.h"

#include <stdlib.h>
#include <string.h>
#include <ctype.h>

static inline char rotate_char(char ch, int shift_key);

static inline char rotate_char(char ch, int shift_key) {
    if (islower(ch)) {
        return 'a' + ((ch - 'a' + shift_key) % 26);
    } else if (isupper(ch)) {
        return 'A' + ((ch - 'A' + shift_key) % 26);
    } else {
        return ch;
    }
}

char *rotate(const char *text, int shift_key) {
    size_t len = strlen(text);
    char *result = malloc(len + 1);
    for (size_t i = 0; i <= len; i += 1) {
        result[i] = rotate_char(text[i], shift_key);
    }
    return result;
}
