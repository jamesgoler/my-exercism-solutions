#include "acronym.h"

#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

static inline size_t abbreviate_len(const char *phrase);

static inline size_t abbreviate_len(const char *phrase) {
    bool take = true;
    size_t len = 0;
    for (const char *ptr = phrase; *ptr != '\0'; ptr += 1) {
        if (isalpha(*ptr)) {
            if (take) {
                len += 1;
                take = false;
            }
        } else if (*ptr == ' ' || *ptr == '-') {
            take = true;
        }
    }
    return len;
}
            
char *abbreviate(const char *phrase) {
    if (!phrase) {
        return NULL;
    }
    size_t len = abbreviate_len(phrase);
    if (len == 0) {
        return NULL;
    }
    bool take = true;
    char *result = malloc(len + 1);
    if (!result) {
        return NULL;
    }
    char *wptr = result;
    for (const char *ptr = phrase; *ptr != '\0'; ptr += 1) {
        if (isalpha(*ptr)) {
            if (take) {
                take = false;
                *(wptr++) = toupper(*ptr);
            }
        } else if (*ptr == ' ' || *ptr == '-') {
            take = true;
        }
    }
    *wptr = '\0';
    return result;
}
