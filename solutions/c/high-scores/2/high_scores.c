#include "high_scores.h"

#include <string.h>

/// Return the latest score.
int32_t latest(const int32_t *scores, size_t scores_len) {
    if (scores_len <= 0) {
        return 0;
    }
    return scores[scores_len - 1];
}

/// Return the highest score.
int32_t personal_best(const int32_t *scores, size_t scores_len) {
    if (scores_len <= 0) {
        return 0;
    }
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
        if (output_len < expect_len) {
            output[output_len] = 0;
            output_len += 1;
        }
        int32_t *o = output + output_len - 1;
        while (o > output && *(o-1) < *ptr) {
            *o = *(o-1);
            o -= 1;
        }
        *o = *ptr;
    }
    return output_len;
}
