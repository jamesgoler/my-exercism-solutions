#include "bob.h"
#include <ctype.h>
#include <stdbool.h>
#include <stddef.h>
#include <string.h>

static inline bool is_question(char *greeting);
static inline bool is_yelling(char *greeting);
static inline bool is_silence(char *greeting);

static inline bool is_question(char *greeting) {
    char *c;
    for (c = greeting + strlen(greeting) - 1; c >= greeting && isspace(*c); c -= 1);
    return *c == '?';
}

static inline bool is_yelling(char *greeting) {
    bool yelling = false;
    for (char *c = greeting; *c != '\0'; c += 1) {
        if (isalpha(*c)) {
            if (!isupper(*c)) {
                return false;
            } else {
                yelling = true;
            }
        }
    }
    return yelling;
}

static inline bool is_silence(char *greeting) {
    for (char *c = greeting; *c != '\0'; c += 1) {
        if (!isspace(*c)) {
            return false;
        }
    }
    return true;
}

char *hey_bob(char *greeting) {
    if (is_silence(greeting)) {
        return "Fine. Be that way!";
    }
    if (is_question(greeting)) {
        if (is_yelling(greeting)) {
            return "Calm down, I know what I'm doing!";
        } else {
            return "Sure.";
        }
    }
    if (is_yelling(greeting)) {
        return "Whoa, chill out!";
    }
    return "Whatever.";
}
