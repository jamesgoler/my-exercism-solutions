#include "two_bucket.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>

static bucket_result_t dfs(bool *seens, bucket_liters_t bucket1, bucket_liters_t bucket2, 
                    bucket_liters_t bucket_size1, bucket_liters_t bucket_size2,
                    bucket_liters_t goal_volume, int steps);

static bucket_result_t dfs(bool *seens, bucket_liters_t bucket1, bucket_liters_t bucket2, 
                    bucket_liters_t bucket_size1, bucket_liters_t bucket_size2,
                    bucket_liters_t goal_volume, int steps) {
    if (bucket1 == goal_volume) {
        return (bucket_result_t) {
            .possible = true,
            .move_count = steps,
            .goal_bucket = 0,
            .other_bucket_liters = bucket2,
        };
    }
    if (bucket2 == goal_volume) {
        return (bucket_result_t) {
            .possible = true,
            .move_count = steps,
            .goal_bucket = 1,
            .other_bucket_liters = bucket1,
        };
    }
    size_t i = bucket1 * (bucket_size2 + 1) + bucket2;
    if (seens[i] || (bucket1 == 0 && bucket2 == bucket_size2)) {
        return (bucket_result_t) {
            .possible = false,
        };
    }
    seens[i] = true;

    bucket_liters_t liters;
    bucket_result_t result;
    bucket_result_t min = (bucket_result_t) {
        .possible = false,
    };

    // action 1. Pouring one bucket into the other bucket until either: a) the first bucket is empty b) the second bucket is full
    liters = (bucket1 <= bucket_size2 - bucket2) ? bucket1 : bucket_size2 - bucket2;
    result = dfs(seens, bucket1 - liters, bucket2 + liters, bucket_size1, bucket_size2, goal_volume, steps + 1);
    if (result.possible && (result.move_count < min.move_count || !min.possible)) {
        min = result;
    }
    liters = (bucket2 <= bucket_size1 - bucket1) ? bucket2 : bucket_size1 - bucket1;
    result = dfs(seens, bucket1 + liters, bucket2 - liters, bucket_size1, bucket_size2, goal_volume, steps + 1);
    if (result.possible && (result.move_count < min.move_count || !min.possible)) {
        min = result;
    }
    
    // action 2. Emptying a bucket and doing nothing to the other.
    result = dfs(seens, 0, bucket2, bucket_size1, bucket_size2, goal_volume, steps + 1);
    if (result.possible && (result.move_count < min.move_count || !min.possible)) {
        min = result;
    }
    result = dfs(seens, bucket1, 0, bucket_size1, bucket_size2, goal_volume, steps + 1);
    if (result.possible && (result.move_count < min.move_count || !min.possible)) {
        min = result;
    }

    // action 3. Filling a bucket and doing nothing to the other.
    result = dfs(seens, bucket_size1, bucket2, bucket_size1, bucket_size2, goal_volume, steps + 1);
    if (result.possible && (result.move_count < min.move_count || !min.possible)) {
        min = result;
    }
    result = dfs(seens, bucket1, bucket_size2, bucket_size1, bucket_size2, goal_volume, steps + 1);
    if (result.possible && (result.move_count < min.move_count || !min.possible)) {
        min = result;
    }
    return min;
}

bucket_result_t measure(bucket_liters_t bucket_1_size,
                        bucket_liters_t bucket_2_size,
                        bucket_liters_t goal_volume, bucket_id_t start_bucket) {   
    if ((bucket_1_size < goal_volume && bucket_2_size < goal_volume) ||
        (bucket_1_size == bucket_2_size && bucket_1_size < goal_volume)) {
        return (bucket_result_t) {
            .possible = false,
        };
    }
    bool *seens = calloc((bucket_1_size + 1) * (bucket_2_size + 1), sizeof(bool));

    bucket_result_t result;
    if (start_bucket == 0) {
        result = dfs(seens, bucket_1_size, 0, bucket_1_size, bucket_2_size, goal_volume, 1);
    } else {
        result = dfs(seens, bucket_2_size, 0, bucket_2_size, bucket_1_size, goal_volume, 1);
    }
    result.goal_bucket = (result.goal_bucket + start_bucket) % 2;
    return result;
}
