#include "perfect_numbers.h"

#include <math.h>

kind classify_number(int n) {
    if (n <= 0) {
        return ERROR;
    }
    if (n == 1) {
        return DEFICIENT_NUMBER;
    }
    int aliquot_sum = 1;

    int nsqrt = (int)sqrt(n);

    for (int i = 2; i <= nsqrt; i += 1) {
        if (n % i == 0) {
            aliquot_sum += i;
            int j = n / i;
            if (j != i) {
                aliquot_sum += j;
            }
        }
    }
    if (aliquot_sum == n) {
        return PERFECT_NUMBER;
    }
    if (aliquot_sum > n) {
        return ABUNDANT_NUMBER;
    }
    return DEFICIENT_NUMBER;
}