#include "phone_number.h"

#include <ctype.h>
#include <stdlib.h>
#include <string.h>

char *phone_number_clean(const char *input) {
    char *result = malloc(10 * sizeof(char) + 1);
    strcpy(result, "0000000000");
    
    while (!isdigit(*input)) {
        input += 1;
    }
    if (*input == '1') {
        input += 1;
    }

    char tmp[11] = { 0 };
    
    size_t i = 0;
    while (*input != '\0') {
        if (isdigit(*input)) {
            if (i == 10 || ((i == 0 || i == 3) && *input <= '1')) {
                return result;
            }
            tmp[i++] = *input;
        }
        input += 1;
    }
    if (i == 10) {
        strcpy(result, tmp);
    }
    return result;
}
