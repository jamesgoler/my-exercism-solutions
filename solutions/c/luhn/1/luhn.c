#include "luhn.h"

#include <ctype.h>
#include <stdlib.h>
#include <string.h>

bool luhn(const char *num) {
    int luhn = 0;
    size_t count = 0;
    bool doubleit = false;
    const char *end = num + strlen(num);
    for (const char *n = end-1; n >= num; n -= 1) {
        if (!isdigit(*n) && !isspace(*n)) {
            return false;
        }
        if (isdigit(*n)) {          
            int d = *n - '0';
            if (doubleit) {
                d <<= 1;
                if (d > 9) {
                    d -= 9;
                }
            }
            luhn = (luhn + d) % 10;
            count += 1;  
            doubleit = !doubleit;
        }
    }
    return count > 1 && luhn % 10 == 0;
}
