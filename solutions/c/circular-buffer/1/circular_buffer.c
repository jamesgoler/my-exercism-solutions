#include "circular_buffer.h"
#include <stdbool.h>

static inline bool is_empty(circular_buffer_t *buffer);
static inline bool is_full(circular_buffer_t *buffer);

static inline bool is_empty(circular_buffer_t *buffer) {
    return buffer->len == 0;
}

static inline bool is_full(circular_buffer_t *buffer) {
    return buffer->len == buffer->capacity;
}

circular_buffer_t *new_circular_buffer(size_t capacity) {
    circular_buffer_t *buf = malloc(sizeof(circular_buffer_t) + (capacity * sizeof(buffer_value_t)));
    buf->capacity = capacity;
    buf->len = 0;
    buf->front = 0;
    return buf;
}

void delete_buffer(circular_buffer_t *buffer) {
    free(buffer);
}

void clear_buffer(circular_buffer_t *buffer) {
    buffer->len = 0;    
}

int16_t read(circular_buffer_t *buffer, buffer_value_t *read_value) {
    if (is_empty(buffer)) {
        errno = ENODATA;
        return EXIT_FAILURE;
    }
    *read_value = buffer->buffer[buffer->front];
    buffer->front = (buffer->front + 1) % buffer->capacity;
    buffer->len -= 1;
    return EXIT_SUCCESS;
}

int16_t write(circular_buffer_t *buffer, buffer_value_t value) {
    if (is_full(buffer)) {
        errno = ENOBUFS;
        return EXIT_FAILURE;
    }
    size_t rear = (buffer->front + buffer->len) % buffer->capacity;
    buffer->buffer[rear] = value;
    buffer->len += 1;
    return EXIT_SUCCESS;
}

int16_t overwrite(circular_buffer_t *buffer, buffer_value_t value) {
    if (write(buffer, value) == EXIT_FAILURE) {
        buffer->buffer[buffer->front] = value;
        buffer->front = (buffer->front + 1) % buffer->capacity;
    }
    return EXIT_SUCCESS;
}
