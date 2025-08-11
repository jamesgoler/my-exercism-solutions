#include "high_scores.h"

#include <string.h>

/// Return the latest score.
int32_t latest(const int32_t *scores, size_t scores_len) {
    return scores[scores_len - 1];
}

/// Return the highest score.
int32_t personal_best(const int32_t *scores, size_t scores_len) {
    int max = scores[0];
    const int32_t *scores_end = scores + scores_len;
    for (const int32_t *ptr = scores; ptr != scores_end; ptr += 1) {
       if (max < *ptr) {
           max = *ptr;
       }  
    }
    return max;
}

/// Write the highest scores to `output` (in non-ascending order).
/// Return the number of scores written.
size_t personal_top_three(const int32_t *scores, size_t scores_len,
                          int32_t *output) {
    int expect_len = (scores_len < 3) ? scores_len : 3;
    int output_len = 0;

    const int32_t *scores_end = scores + scores_len;
    for (const int32_t *ptr = scores; ptr != scores_end; ptr += 1) {
        int32_t value = *ptr;
        const int32_t *output_end = output + output_len;
        for (int32_t *o = output; o < output_end; o += 1) {
            if (*ptr > *o) {
                int32_t tmp = *o;
                *o = value;
                value = tmp;
            }
        }
        if (output_len < expect_len) {
            output[output_len++] = value;
        }
    }
    return output_len;
}
