#include "atbash_cipher.h"
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>

static inline char atbash(const char ch) {
    if (isalpha(ch)) {
        return 'z' - ch + 'a';
    }
    return ch;
}

char *atbash_encode(const char *input) {
    if (!input) {
        return NULL;
    }
    size_t len = 0;
    for (const char *ch = input; *ch != '\0'; ch += 1) {
        if (isalnum(*ch)) {
            len += 1;
        }
    }
    if (len == 0) {
        return calloc(1, 1);
    }
    char *result = malloc((len + ((len-1) / 5) + 1) * sizeof(char));
    char *wptr = result;
    size_t i = 0;
    for (const char *ch = input; *ch != '\0'; ch += 1) {
        if (isalnum(*ch)) {
            *(wptr++) = atbash(tolower(*ch));
            i = (i + 1) % 5;
            if (i == 0) {
                *(wptr++) = ' ';
            }
        }
    }
    if (*(wptr-1) == ' ') {
        *(wptr-1) = '\0';
    } else {
        *wptr = '\0';
    }
    return result;
}

char *atbash_decode(const char *input) {
    if (!input) {
        return NULL;
    }
    size_t len = strlen(input);
    if (len == 0) {
        return calloc(1, 1);
    }
    char *result = malloc((len + 1) * sizeof(char));
    char *wptr = result;
    for (const char *ch = input; *ch != '\0'; ch += 1) {
        if (isalnum(*ch)) {
            *(wptr++) = atbash(*ch);
        }
    }
    *wptr = '\0';
    return result;
}
