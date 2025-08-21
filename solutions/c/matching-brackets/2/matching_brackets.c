#include "matching_brackets.h"

#include <stdlib.h>
#include <string.h>

static inline bool is_opening(char input);
static inline bool is_closing(char input);
static inline char get_closing(char input);

static inline bool is_opening(char input) {
    return strchr("({[", input);
}
static inline bool is_closing(char input) {
    return strchr(")}]", input);
}

static inline char get_closing(char input) {
    switch (input) {
    case '(':
        return ')';
    case '{':
        return '}';
    case '[':
        return ']';    
    }
    return '\0';
}

bool is_paired(const char *input) {
    if (!input) {
        return true;
    }
    char *closes = malloc(strlen(input) + 1);
    if (!closes) {
        return false;
    }
    size_t top = 0;
    for (const char *ptr = input; *ptr != '\0'; ptr += 1) {
        if (is_opening(*ptr)) {
            closes[top++] = get_closing(*ptr);
        } else if (is_closing(*ptr)) {
            if (top == 0 || closes[top - 1] != *ptr) {
                free(closes);
                return false;
            }
            top -= 1;
        }
    }
    free(closes);
    return top == 0;
}