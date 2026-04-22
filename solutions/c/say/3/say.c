#include "say.h"
#include <stddef.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

struct string_buffer {
    char *data;
    size_t len;
    size_t cap;
};

static inline int string_buffer_init(struct string_buffer *buf, size_t cap);
static inline void string_buffer_destroy(struct string_buffer *buf);
static inline int string_buffer_extend(struct string_buffer *buf, const char *b);
static inline int string_buffer_reserve(struct string_buffer *buf, size_t additional);
static inline char *string_buffer_to_string(struct string_buffer *buf);

static inline int string_buffer_init(struct string_buffer *buf, size_t cap)
{
    buf->data = malloc(sizeof(char) * cap);
    if (!buf->data)
        return -1;
    buf->cap = cap;
    buf->len = 0;
    return 0;
}

static inline void string_buffer_destroy(struct string_buffer *buf)
{
    free(buf->data);
    buf->data = NULL;
    buf->len = 0;
    buf->cap = 0;
}

static inline int string_buffer_extend(struct string_buffer *buf, const char *b)
{
    size_t len = strlen(b);
    if (string_buffer_reserve(buf, len) == -1)
        return -1;
    memcpy(buf->data + buf->len, b, len);
    buf->len += len;
    return 0;
}

static inline int string_buffer_reserve(struct string_buffer *buf, size_t additional)
{
    if (buf->cap - buf->len < additional) {
        size_t cap_additional = additional - (buf->cap - buf->len);
        if (SIZE_MAX - cap_additional < buf->cap)
            return -1;
        char *tmp = realloc(buf->data, buf->cap + cap_additional);
        if (!tmp)
            return -1;
        buf->data = tmp;
        buf->cap = buf->cap + cap_additional;
    }
    return 0;
}

static inline char *string_buffer_to_string(struct string_buffer *buf)
{
    char *s = malloc(sizeof(char) * (buf->len + 1));
    if (!s)
       return NULL;
    memcpy(s, buf->data, buf->len);
    s[buf->len] = '\0';
    return s;
}

static inline bool is_valid(int64_t input);
static inline int parse_under_thousand(struct string_buffer *buf, int64_t input);
static inline char *parse_teens(int64_t input);
static inline char *parse_tens(int64_t input);
static inline char *parse_under_ten(int64_t input);

static inline bool is_valid(int64_t input)
{
    return input >= 0 && input <= 999999999999;
}

static inline int parse_under_thousand(struct string_buffer *buf, int64_t input)
{
    int64_t hundred = input / 100;
    if (hundred > 0) {
        if (string_buffer_extend(buf, parse_under_ten(hundred)) == -1)
            return -1;
        if (string_buffer_extend(buf, " hundred") == -1)
            return -1;
        if (input % 100 > 0) {
            if (string_buffer_extend(buf, " ") == -1)
                return -1;
        }
    }
    input %= 100;
    if (input >= 20) {
        if (string_buffer_extend(buf, parse_tens(input / 10)) == -1)
            return -1;
        input %= 10;
        if (input > 0) {
            if (string_buffer_extend(buf, "-") == -1)
                return -1;
            if (string_buffer_extend(buf, parse_under_ten(input)) == -1)
                return -1;
        }
    } else if (input >= 10) {
        if (string_buffer_extend(buf, parse_teens(input)) == -1)
            return -1;
    } else if (input > 0) {
        if (string_buffer_extend(buf, parse_under_ten(input)) == -1)
            return -1;
    }
    return 0;
}

static inline char *parse_teens(int64_t input)
{
    switch (input) {
    case 10:
        return "ten";
    case 11:
        return "eleven";
    case 12:
        return "twelve";
    case 13:
        return "thirteen";
    case 14:
        return "fourteen";
    case 15:
        return "fifteen";
    case 16:
        return "sixteen";
    case 17:
        return "seventeen";
    case 18:
        return "eighteen";
    case 19:
        return "nineteen";
    default:
        return "";
    }
}

static inline char *parse_tens(int64_t input)
{
    switch (input) {
    case 1:
        return "ten";
    case 2:
        return "twenty";
    case 3:
        return "thirty";
    case 4:
        return "forty";
    case 5:
        return "fifty";
    case 6:
        return "sixty";
    case 7:
        return "seventy";
    case 8:
        return "eighty";
    case 9:
        return "ninety";
    default:
        return "";
    }
}

static inline char *parse_under_ten(int64_t input)
{
    switch (input) {
    case 1:
        return "one";
    case 2:
        return "two";
    case 3:
        return "three";
    case 4:
        return "four";
    case 5:
        return "five";
    case 6:
        return "six";
    case 7:
        return "seven";
    case 8:
        return "eight";
    case 9:
        return "nine";
    default:
        return "";
    }
}

int say(int64_t input, char **ans)
{
    *ans = NULL;

    if (!is_valid(input))
        return -1;

    struct string_buffer buf;
    if (string_buffer_init(&buf, 1024) == -1)
        return -1;

    if (input == 0) {
        if (string_buffer_extend(&buf, "zero") == -1)
            goto out;
    } else {
        const char *SUFFIX_NAMES[] = {" billion", " million", " thousand", ""};
        const int64_t SUFFICES[] = {1000000000, 1000000, 1000, 1};
        const size_t SUFFIX_NUM = 4;
        for (size_t i = 0; i < SUFFIX_NUM; i += 1) {
            if (input >= SUFFICES[i]) {
                int64_t next_input = input % SUFFICES[i];
                input /= SUFFICES[i];
                if (parse_under_thousand(&buf, input) == -1)
                    goto out;
                if (string_buffer_extend(&buf, SUFFIX_NAMES[i]) == -1)
                    goto out;
                if (next_input > 0) {
                    if (string_buffer_extend(&buf, " ") == -1)
                        goto out;
                }
                input = next_input;
            }
        }
    }
    *ans = string_buffer_to_string(&buf);
out:
    string_buffer_destroy(&buf);
    return *ans ? 0 : -1;
}
