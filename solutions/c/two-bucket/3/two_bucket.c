#include "two_bucket.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>

struct queue_entry {
    bucket_liters_t bucket1;
    bucket_liters_t bucket2;
    int steps;
};

struct queue {
    size_t cur;
    size_t len;
    size_t cap;
    bucket_liters_t bucket_size1;
    bucket_liters_t bucket_size2;
    struct queue_entry *entries;
    bool *seens;
};

static inline struct queue create_queue(size_t size);
static inline void destroy_queue(struct queue *queue);
static inline void push_back_queue(struct queue *queue, bucket_liters_t bucket1, bucket_liters_t bucket2, int steps);
static inline struct queue_entry pop_front_queue(struct queue *queue);
static inline bool is_empty(struct queue *queue);
static bucket_result_t bfs(struct queue *queue, bucket_liters_t goal_volume);

static inline struct queue create_queue(size_t size) {
    struct queue queue;
    queue.entries = malloc(size * sizeof(struct queue_entry));
    queue.seens = calloc(size, sizeof(bool));
    queue.cur = 0;
    queue.len = 0;
    queue.cap = size;
    return queue;
}

static inline void destroy_queue(struct queue *queue) {
    if (queue) {
        free(queue->entries);
        free(queue->seens);
    }
}

static inline void push_back_queue(struct queue *queue, bucket_liters_t bucket1, bucket_liters_t bucket2, int steps) {
    if (queue->len >= queue->cap) {
        exit(EXIT_FAILURE);
    }
    size_t i = bucket1 * (queue->bucket_size2 + 1) + bucket2;
    if (!queue->seens[i] && !(bucket1 == 0 && bucket2 == queue->bucket_size2)) {
        queue->entries[queue->len++] = (struct queue_entry) {
            .bucket1 = bucket1,
            .bucket2 = bucket2,
            .steps = steps,
        };
        queue->seens[i] = true;
    }
}

static inline struct queue_entry pop_front_queue(struct queue *queue) {
    if (is_empty(queue)) {
        exit(EXIT_FAILURE);
    }
    return queue->entries[queue->cur++];
}

static inline bool is_empty(struct queue *queue) {
    return queue->cur == queue->len;
}

static bucket_result_t bfs(struct queue *queue, bucket_liters_t goal_volume) {
    while (!is_empty(queue)) {
        struct queue_entry qe = pop_front_queue(queue);

        bucket_liters_t buckets[] = { qe.bucket1, qe.bucket2 };
        for (bucket_id_t i = 0; i < 2; i += 1) {
            if (buckets[i] == goal_volume) {
                return (bucket_result_t) {
                    .possible = true,
                    .move_count = qe.steps,
                    .goal_bucket = i,
                    .other_bucket_liters = buckets[(i + 1) % 2],
                };
            }
        }

        bucket_liters_t liters;

        // 1. Pouring one bucket into the other bucket until either:
        //     a) the first bucket is empty
        //     b) the second bucket is full
        liters = (qe.bucket1 <= queue->bucket_size2 - qe.bucket2) ? qe.bucket1 : queue->bucket_size2 - qe.bucket2;
        push_back_queue(queue, qe.bucket1 - liters, qe.bucket2 + liters, qe.steps + 1);

        liters = (qe.bucket2 <= queue->bucket_size1 - qe.bucket1) ? qe.bucket2 : queue->bucket_size1 - qe.bucket1;
        push_back_queue(queue, qe.bucket1 + liters, qe.bucket2 - liters, qe.steps + 1);

        // 2. Emptying a bucket and doing nothing to the other.
        push_back_queue(queue, 0, qe.bucket2, qe.steps + 1);
        push_back_queue(queue, qe.bucket1, 0, qe.steps + 1);

        // 3. Filling a bucket and doing nothing to the other.
        push_back_queue(queue, queue->bucket_size1, qe.bucket2, qe.steps + 1);
        push_back_queue(queue, qe.bucket1, queue->bucket_size2, qe.steps + 1);
    }
    return (bucket_result_t) {
        .possible = false,
    };
}

bucket_result_t measure(bucket_liters_t bucket_1_size,
                        bucket_liters_t bucket_2_size,
                        bucket_liters_t goal_volume, bucket_id_t start_bucket) {
    if ((bucket_1_size < goal_volume && bucket_2_size < goal_volume)) {
        return (bucket_result_t) {
            .possible = false,
        };
    }
    size_t size = (bucket_1_size + 1) * (bucket_2_size + 1);
    struct queue queue = create_queue(size);

    if (start_bucket == BUCKET_ID_1) {
        queue.bucket_size1 = bucket_1_size;
        queue.bucket_size2 = bucket_2_size;
        push_back_queue(&queue, bucket_1_size, 0, 1);
    } else {
        queue.bucket_size1 = bucket_2_size;
        queue.bucket_size2 = bucket_1_size;
        push_back_queue(&queue, bucket_2_size, 0, 1);
    }
    bucket_result_t result = bfs(&queue, goal_volume);
    result.goal_bucket = (result.goal_bucket + start_bucket) % 2;
    destroy_queue(&queue);
    return result;
}