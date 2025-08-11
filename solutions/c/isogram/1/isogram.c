#include "isogram.h"

#include <ctype.h>

bool is_isogram(const char phrase[]) {
    int seen_map = 0;

    if (!phrase) {
        return false;
    }

    for (const char *ptr = phrase; *ptr != '\0'; ptr += 1) {
        if (isalpha(*ptr)) {
            int i = 1 << (tolower(*ptr) - 'a');
            if (seen_map & i) {
                return false;
            }
            seen_map |= i;
        }
    }
    return true;
}