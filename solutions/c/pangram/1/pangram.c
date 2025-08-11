#include "pangram.h"

#include <ctype.h>

bool is_pangram(const char *sentence) {
    if (!sentence) {
        return false;
    }
    
    int expect_check_map = 0;
    for (int i = 0; i < 26; i += 1) {
        expect_check_map |= 1 << i;
    }
    
    int check_map = 0;
    for (const char *ptr = sentence; *ptr != '\0'; ptr += 1) {
        if (isalpha(*ptr)) {
            check_map |= 1 << (tolower(*ptr) - 'a');
            if (check_map == expect_check_map) {
                return true;
            }
        }
    }
    return false;
}
