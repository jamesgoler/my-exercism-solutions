#include "reverse_string.h"

#include <string.h>
#include <stdlib.h>

char *reverse(const char *value) {
    if (!value) {
        return NULL;
    }
    size_t len = strlen(value);
    char *res = malloc(len + 1);
    if (!res) {
        return NULL;
    }
    char *ptr = res;
    const char *vptr = value + len - 1;
    while (vptr >= value) {
        *ptr++ = *vptr--;
    }
    *ptr = '\0';
    return res;
}