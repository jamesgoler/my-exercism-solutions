#define _GNU_SOURCE
#include "raindrops.h"

#include <stdio.h>
#include <string.h>

void convert(char result[], int drops) {
    result[0] = '\0';
    char *ptr = result;
    if (drops % 3 == 0) {
        ptr = stpcpy(ptr, "Pling");
    }
    if (drops % 5 == 0) {
        ptr = stpcpy(ptr, "Plang");
    }
    if (drops % 7 == 0) {
        ptr = stpcpy(ptr, "Plong");
    }
    if (result[0] == '\0') {
        sprintf(result, "%d", drops);
    }
}