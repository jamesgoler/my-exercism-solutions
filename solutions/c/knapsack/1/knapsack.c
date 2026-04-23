#include "knapsack.h"

#include <stdlib.h>
#include <stddef.h>

unsigned int maximum_value(unsigned int max_weight, item_t *items, size_t item_count)
{
    unsigned int answer = 0;

    unsigned int *dp = calloc((max_weight + 1) * 2, sizeof(unsigned int));
    if (!dp)
        goto quit;

    size_t cur = 0;
    size_t prev = (max_weight + 1);
    for (size_t i = 0; i < item_count; i += 1) {
        for (size_t w = 0; w <= max_weight; w += 1) {
            dp[cur + w] = dp[prev + w];

            if (items[i].weight <= w) {
                unsigned int v = dp[prev + w - items[i].weight] + items[i].value;
                if (v > dp[cur + w])
                    dp[cur + w] = v;
            }
        }
        size_t tmp = cur;
        cur = prev;
        prev = tmp;
    }
    answer = dp[prev + max_weight];

    free(dp);
quit:
    return answer;
}
