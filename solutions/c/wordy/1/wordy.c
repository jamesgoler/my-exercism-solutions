#include "wordy.h"
#include <ctype.h>
#include <stdbool.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>

#define OP_ADD_PAT "plus "
#define OP_SUB_PAT "minus "
#define OP_MUL_PAT "multiplied by "
#define OP_DIV_PAT "divided by "
#define OP_ADD_LEN sizeof(OP_ADD_PAT) - 1
#define OP_SUB_LEN sizeof(OP_SUB_PAT) - 1
#define OP_MUL_LEN sizeof(OP_MUL_PAT) - 1
#define OP_DIV_LEN sizeof(OP_DIV_PAT) - 1

enum operator {
    OP_NOOP,
    OP_ADD,
    OP_SUB,
    OP_MUL,
    OP_DIV,
    OP_ERR,
};

static inline bool parse_operand(const char *str, int *operand, const char **saveptr);
static inline bool parse_operator(const char *str, enum operator *operator, const char **saveptr);
static inline int apply_operator(int operand1, enum operator operator, int operand2);
static inline bool skip_spaces(const char *str, const char **saveptr);

static inline bool parse_operand(const char *str, int *operand, const char **saveptr) {
    if (!skip_spaces(str, &str)) {
        return false;
    }
    *operand = strtoll(str, (char **)saveptr, 10);
    return isspace(**saveptr) || **saveptr == '?';
}

static inline bool parse_operator(const char *str, enum operator *operator, const char **saveptr) {
    if (!skip_spaces(str, &str)) {
        return false;
    }
    if (strncmp(str, OP_ADD_PAT, OP_ADD_LEN) == 0) {
        *operator = OP_ADD;
        *saveptr = str + OP_ADD_LEN;
    } else if (strncmp(str, OP_SUB_PAT, OP_SUB_LEN) == 0) {
        *operator = OP_SUB;
        *saveptr = str + OP_SUB_LEN;
    } else if (strncmp(str, OP_MUL_PAT, OP_MUL_LEN) == 0) {
        *operator = OP_MUL;
        *saveptr = str + OP_MUL_LEN;
    } else if (strncmp(str, OP_DIV_PAT, OP_DIV_LEN) == 0) {
        *operator = OP_DIV;
        *saveptr = str + OP_DIV_LEN;
    } else {
        *operator = (strcmp(str, "?") == 0) ? OP_NOOP : OP_ERR;
        return false;
    }
    return true;
}

static inline int apply_operator(int operand1, enum operator operator, int operand2) {
    switch (operator) {
    case OP_ADD:
        return operand1 + operand2;
    case OP_SUB:
        return operand1 - operand2;
    case OP_MUL:
        return operand1 * operand2;
    case OP_DIV:
        return operand1 / operand2;
    default:
        return 0;
    }
}

static inline bool skip_spaces(const char *str, const char **saveptr) {
    while (isspace(*str)) {
        str += 1;
    }
    *saveptr = str;
    return *str != '\0';
}

bool answer(const char *question, int *result) {
    size_t len = strlen(question);
    const char *question_end = question + len - 1;
    if (!question || strncmp(question, "What is ", 8) || *question_end != '?') {
        return false;
    }
    question += 8;

    if (!parse_operand(question, result, &question)) {
        return false;
    }

    enum operator operator = OP_NOOP;
    while (parse_operator(question, &operator, &question)) {
        int operand;
        if (!parse_operand(question, &operand, &question)) {
            return false;
        }
        *result = apply_operator(*result, operator, operand);
    }
    return operator != OP_ERR;
}
