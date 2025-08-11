#include "sum_of_multiples.h"

unsigned int sum(const unsigned int *factors, const size_t number_of_factors,
                 const unsigned int limit)
{
    unsigned int res = 0;
    for (unsigned int n = 1; n < limit; n += 1) {
        for (unsigned int j = 0; j < number_of_factors; j += 1) {
            if (factors[j] > 0 && n % factors[j] == 0) {
                res += n;
                break;
            }
        }
    }
    return res;
}