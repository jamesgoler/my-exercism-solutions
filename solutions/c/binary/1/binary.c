#include "binary.h"

#include <string.h>

int convert(const char *input) {
    int result = 0;
    for (const char *ptr = input; *ptr != '\0'; ptr += 1) {
        if (ptr - input + 1 > 32 || !strchr("01", *ptr)) {
            return INVALID;
        }
        result = (result << 1) + (*ptr - '0');
    }
    return result;
}
