#include "run_length_encoding.h"

#include <ctype.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

static inline size_t count_digit(size_t n);
static inline size_t encoded_len(const char *text, size_t text_len);
static inline size_t decoded_len(const char *text, size_t text_len);

static inline size_t count_digit(size_t n) {
    size_t digits = 0;
    if (n > 1) {
        while (n > 0) {
            digits += 1;
            n /= 10;
        }
    }
    return digits;
}

static inline size_t encoded_len(const char *text, size_t text_len) {
    size_t len = 0;
    size_t count = 0;
    char prev_ch = text[0];
    const char *end = text + text_len + 1; // use '\0' as sentinel to handle last char.
    for (const char *ptr = text; ptr < end; ptr += 1) {
        if (*ptr == prev_ch) {
            count += 1;
        } else {
            len += 1 + count_digit(count);
            count = 1;
            prev_ch = *ptr;
        }
    }
    return len;
}

static inline size_t decoded_len(const char *text, size_t text_len) {
    size_t len = 0;
    size_t count = 0;
    const char *end = text + text_len + 1; // use '\0' as sentinel to handle last char.
    for (const char *ptr = text; ptr < end; ptr += 1) {
        if (isdigit(*ptr)) {
            count = count * 10 + *ptr - '0';
        } else {
            if (count == 0) {
                len += 1;
            } else {
                len += count;
            }
            count = 0;
        }
    }
    return len;
}

char *encode(const char *text) {
    if (!text) {
        return NULL;
    }
    size_t text_len = strlen(text);
    size_t len = encoded_len(text, text_len);
    char *result = malloc(len + 1);

    char *wptr = result;
    size_t count = 0;
    char prev_ch = text[0];
    const char *end = text + text_len + 1; // use '\0' as sentinel to handle last char.
    for (const char *rptr = text; rptr < end; rptr += 1) {
        if (*rptr == prev_ch) {
            count += 1;
        } else {
            if (count > 1) {
                sprintf(wptr, "%ld", count);
                wptr += count_digit(count);
            }
            count = 1;
            *(wptr++) = prev_ch;
            prev_ch = *rptr;
        }
    }
    *wptr = '\0';
    return result;
}

char *decode(const char *data) {
    if (!data) {
        return NULL;
    }
    size_t text_len = strlen(data);
    size_t len = decoded_len(data, text_len);
    char *result = malloc(len + 1);

    char *wptr = result;
    size_t count = 0;
    const char *end = data + text_len + 1; // use '\0' as sentinel to handle last char.
    for (const char *rptr = data; rptr < end; rptr += 1) {
        if (isdigit(*rptr)) {
            count = count * 10 + *rptr - '0';
        } else {
            if (count == 0) {
                count = 1;
            }
            for (size_t c = 0; c < count; c += 1) {
                *(wptr++) = *rptr;
            }
            count = 0;
        }
    }
    *wptr = '\0';
    return result;
}
