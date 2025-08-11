#include "armstrong_numbers.h"

#include <math.h>

bool is_armstrong_number(int candidate) {
    int tmp = candidate;
    int power = 0;
    while (tmp > 0) {
        tmp /= 10;
        power += 1;
    }
    if (power == 0) {
        power += 1;
    }
    int sum = 0;
    tmp = candidate;
    while (tmp > 0) {
        int d = tmp % 10;
        tmp /= 10;
        sum += pow(d, power);
    }
    return sum == candidate;
}