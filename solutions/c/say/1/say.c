#include "say.h"
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

static inline bool is_valid(int64_t input);
static inline char *parse_under_thousand(int64_t input);
static inline char *parse_tens(int64_t input);
static inline char *parse_teens(int64_t input);
static inline char *parse_under_ten(int64_t input);
static inline char *extend_string(char *a, const char *b);
static inline char *say_unchecked(int64_t input);

static inline bool is_valid(int64_t input) {
    return input >= 0 && input <= 999999999999;
}

static inline char *parse_under_thousand(int64_t input)
{
    char *result = NULL;
    int64_t hundred = input / 100;
    if (hundred > 0) {
        result = extend_string(result, parse_under_ten(hundred));
        result = extend_string(result, " hundred");
        if (input % 100 > 0) {
            result = extend_string(result, " ");
        }
    }
    input %= 100;
    if (input >= 20) {
        result = extend_string(result, parse_tens(input / 10));
        input %= 10;
        if (input > 0) {
            result = extend_string(result, "-");
            result = extend_string(result, parse_under_ten(input));
        }
    } else if (input >= 10) {
        result = extend_string(result, parse_teens(input));
    } else if (input > 0) {
        result = extend_string(result, parse_under_ten(input));
    }
    return result;
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
    case 0:
        return "zero";
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
    case 0:
        return "zero";
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

static inline char *extend_string(char *a, const char *b)
{
    size_t alen = a ? strlen(a) : 0;
    a = realloc(a, alen + strlen(b) + 1);
    strcpy(a + alen, b);
    return a;
}

static inline char *say_unchecked(int64_t input)
{
    const char *SUFFIX_NAMES[] = {" billion", " million", " thousand", ""};
    const int64_t SUFFICES[] = {1000000000, 1000000, 1000, 1};
    const size_t SUFFIX_NUM = 4;

    char *ans = NULL;
    if (input == 0) {
        return extend_string(ans, "zero");
    }
    for (size_t i = 0; i < SUFFIX_NUM; i += 1) {
        if (input >= SUFFICES[i]) {
            int64_t suffix = SUFFICES[i];
            const char *suffix_name = SUFFIX_NAMES[i];

            int64_t next_input = input % suffix;
            input /= suffix;
            ans = extend_string(ans, parse_under_thousand(input));
            ans = extend_string(ans, suffix_name);
            if (next_input == 0) {
                break;
            } else {
                ans = extend_string(ans, " ");
            }
            input = next_input;
        }
    }
    return ans;
}

int say(int64_t input, char **ans)
{
    if (!is_valid(input)) {
        return -1;
    }
    *ans = say_unchecked(input);
    return 0;
}
