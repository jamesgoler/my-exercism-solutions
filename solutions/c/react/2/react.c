#include "react.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdbool.h>

struct callback_info {
    callback fn;
    void *args;
};

struct vector {
    void *elements;
    size_t size;
    size_t len;
    size_t cap;
};

struct reactor {
    struct vector cells;
};

enum cell_kind {
    UNINITIALIZED,
    INPUT,
    COMPUTE1,
    COMPUTE2,
};

// struct input_cell {
// };

struct compute1_cell {
    compute1 operation;
    struct cell *operand;
};

struct compute2_cell {
    compute2 operation;
    struct cell *operand1;
    struct cell *operand2;
};

struct cell {
    size_t id;
    int value;
    bool visit;
    enum cell_kind kind;
    union cell_variant {
        // struct input_cell input;
        struct compute1_cell comp1;
        struct compute2_cell comp2;
    } variant;
    struct vector callbacks;
    struct vector notification_list;
};

static inline void init_vector(struct vector *v, size_t size);
static inline void destroy_vector(struct vector *v);
static inline void *allocate_element_vector(struct vector *v);
static inline int reserve_vector(struct vector *v, size_t additional);
static inline size_t available_vector(struct vector *v);
static inline void *nth_vector(struct vector *v, size_t n);
static inline size_t offset_vector(struct vector *v, void *element);
static inline void sort_vector(struct vector *v, int (*compare_fn)(const void *, const void *));
static inline void *allocate_element_callbacks(struct vector *callbacks);
static inline void *find_deleted_callbacks(struct vector *callbacks);
static inline void add_notification(struct cell *cell, struct cell *recipient);
static inline struct vector create_notification_queue(struct cell *cell);
static inline void destroy_notification_queue(struct vector *queue);
static inline void collect_notifications(struct vector *queue, struct cell *cell);
static int compare_cells(const void *v1, const void *v2);
static inline struct cell *create_blank_cell(struct reactor *r);
static inline void destroy_cell(struct cell *c);
static inline int compute_cell_value(struct cell *cell);
static inline int update_cell_value(struct cell *cell, int new_value);

static inline void init_vector(struct vector *v, size_t size)
{
    v->elements = NULL;
    v->size = size;
    v->len = 0;
    v->cap = 0;
}

static inline void destroy_vector(struct vector *v)
{
    free(v->elements);
    v->elements = NULL;
}

static inline void *allocate_element_vector(struct vector *v)
{
    if (reserve_vector(v, 1) < 0)
        return NULL;
    return nth_vector(v, v->len++);
}

static inline int reserve_vector(struct vector *v, size_t additional)
{
    size_t available = available_vector(v);
    if (available >= additional)
        return 0;

    size_t new_cap = v->cap + additional - available;
    if ((v->cap << 1) > new_cap)
        new_cap = v->cap << 1;

    void *new_elements = realloc(v->elements, new_cap * v->size);
    if (!new_elements)
        return -errno;

    v->cap = new_cap;
    v->elements = new_elements;
    return 0;
}

static inline size_t available_vector(struct vector *v)
{
    return v->cap - v->len;
}

static inline void *nth_vector(struct vector *v, size_t n)
{
    if (n >= v->len)
        return NULL;
    return (char *)v->elements + (n * v->size);
}

static inline size_t offset_vector(struct vector *v, void *element)
{
    if (element < v->elements)
        return 0;
    return ((char *)element - (char *)v->elements) / v->size;
}

static inline void sort_vector(struct vector *v, int (*compare_fn)(const void *, const void *))
{
    qsort(v->elements, v->len, v->size, compare_fn);
}

static inline void *allocate_element_callbacks(struct vector *callbacks)
{
    struct callback_info *ptr = find_deleted_callbacks(callbacks);
    if (ptr)
        return ptr;
    return allocate_element_vector(callbacks);
}

static inline void *find_deleted_callbacks(struct vector *callbacks)
{
    for (size_t i = 0; i < callbacks->len; i += 1) {
        struct callback_info *ptr = nth_vector(callbacks, i);
        if (!ptr->fn)
            return ptr;
    }
    return NULL;
}

static inline void add_notification(struct cell *cell, struct cell *recipient)
{
    struct cell **ptr = allocate_element_vector(&cell->notification_list);
    if (!ptr)
        exit(EXIT_FAILURE);

    *ptr = recipient;
}

static inline struct vector create_notification_queue(struct cell *cell)
{
    struct vector queue;
    init_vector(&queue, sizeof(struct cell *));
    collect_notifications(&queue, cell);
    sort_vector(&queue, compare_cells);
    return queue;
}

static inline void destroy_notification_queue(struct vector *queue)
{
    for (size_t i = 0; i < queue->len; i += 1) {
        struct cell **c = nth_vector(queue, i);
        (*c)->visit = false;
    }
    destroy_vector(queue);
}

static inline void collect_notifications(struct vector *queue, struct cell *cell)
{
    for (size_t i = 0; i < cell->notification_list.len; i += 1) {
        struct cell **c = nth_vector(&cell->notification_list, i);
        if ((*c)->visit)
            continue;

        (*c)->visit = true;

        struct cell **ptr = allocate_element_vector(queue);
        if (!ptr)
            exit(EXIT_FAILURE);

        *ptr = *c;
        collect_notifications(queue, *c);
    }
}

struct reactor *create_reactor(void)
{
    struct reactor *r = malloc(sizeof(struct reactor));
    if (!r)
        return NULL;

    init_vector(&r->cells, sizeof(struct cell *));
    return r;
}

void destroy_reactor(struct reactor *r)
{
    for (size_t i = 0; i < r->cells.len; i += 1) {
        struct cell **c = nth_vector(&r->cells, i);
        destroy_cell(*c);
        free(*c);
    }
    destroy_vector(&r->cells);
    free(r);
}

static int compare_cells(const void *v1, const void *v2)
{
    const struct cell **c1 = (const struct cell **)v1;
    const struct cell **c2 = (const struct cell **)v2;

    if ((*c1)->id > (*c2)->id)
        return 1;
    if ((*c1)->id < (*c2)->id)
        return -1;
    return 0;
}

static inline struct cell *create_blank_cell(struct reactor *r)
{
    struct cell **cell = allocate_element_vector(&r->cells);
    if (!cell)
        return NULL;

    *cell = malloc(sizeof(struct cell));
    if (!*cell)
        return NULL;

    (*cell)->id = offset_vector(&r->cells, *cell);
    (*cell)->visit = false;
    (*cell)->kind = UNINITIALIZED;
    init_vector(&(*cell)->callbacks, sizeof(struct callback_info));
    init_vector(&(*cell)->notification_list, sizeof(struct cell *));
    return *cell;
}

struct cell *create_input_cell(struct reactor *r, int initial_value)
{
    struct cell *cell = create_blank_cell(r);
    if (!cell)
        return NULL;

    cell->kind = INPUT;
    cell->value = initial_value;
    return cell;
}

struct cell *create_compute1_cell(struct reactor *r, struct cell *c, compute1 fn)
{
    struct cell *cell = create_blank_cell(r);
    if (!cell)
        return NULL;

    cell->kind = COMPUTE1;
    cell->variant.comp1 = (struct compute1_cell) {
        .operand = c,
        .operation = fn,
    };
    cell->value = fn(c->value);

    add_notification(c, cell);
    return cell;
}

struct cell *create_compute2_cell(struct reactor *r, struct cell *c1, struct cell *c2, compute2 fn)
{
    struct cell *cell = create_blank_cell(r);
    if (!cell)
        return NULL;

    cell->kind = COMPUTE2;
    cell->variant.comp2 = (struct compute2_cell) {
        .operand1 = c1,
        .operand2 = c2,
        .operation = fn,
    };
    cell->value = fn(c1->value, c2->value);

    add_notification(c1, cell);
    add_notification(c2, cell);
    return cell;
}

static inline void destroy_cell(struct cell *c)
{
    if (!c)
        return;
    destroy_vector(&c->callbacks);
    destroy_vector(&c->notification_list);
}

static inline int compute_cell_value(struct cell *cell)
{
    switch (cell->kind) {
    case INPUT:
        return cell->value;
    case COMPUTE1:
        return cell->variant.comp1.operation(
            cell->variant.comp1.operand->value
        );
    case COMPUTE2:
        return cell->variant.comp2.operation(
            cell->variant.comp2.operand1->value,
            cell->variant.comp2.operand2->value
        );
    default:
        fprintf(stderr, "Unknown cell kind: %d\n", cell->kind);
        exit(EXIT_FAILURE);
    };
}

int get_cell_value(struct cell *cell)
{
    return cell->value;
}

void set_cell_value(struct cell *cell, int new_value)
{
    if (cell->kind != INPUT)
        return;

    if (update_cell_value(cell, new_value) == -1)
        return;

    struct vector queue = create_notification_queue(cell);
    for (size_t i = 0; i < queue.len; i += 1) {
        struct cell **c = nth_vector(&queue, i);
        update_cell_value(*c, compute_cell_value(*c));
    }
    destroy_notification_queue(&queue);
}

static inline int update_cell_value(struct cell *cell, int new_value)
{
    if (new_value == cell->value)
        return -1;

    cell->value = new_value;

    for (size_t i = 0; i < cell->callbacks.len; i += 1) {
        struct callback_info *cb = nth_vector(&cell->callbacks, i);
        if (cb->fn)
            cb->fn(cb->args, cell->value);
    }
    return 0;
}

callback_id add_callback(struct cell *cell, void *args, callback fn)
{
    struct callback_info *ptr = allocate_element_callbacks(&cell->callbacks);
    if (!ptr)
        return 0;

    *ptr = (struct callback_info) {
        .fn = fn,
        .args = args,
    };
    return offset_vector(&cell->callbacks, ptr);
}

void remove_callback(struct cell *cell, callback_id id)
{
    struct callback_info *info = nth_vector(&cell->callbacks, id);
    if (!info)
        return;

    *info = (struct callback_info) {
        .fn = NULL,
        .args = NULL,
    };
}
