#include "linked_list.h"
#include <stddef.h>
#include <stdlib.h>
#include <stdbool.h>

struct list_node {
   struct list_node *prev, *next;
   ll_data_t data;
};

struct list {
   struct list_node *first, *last;
   size_t count;
};

static inline struct list_node *list_node_create(ll_data_t data);

static inline struct list_node *list_node_create(ll_data_t data) {
    struct list_node *node = malloc(sizeof(struct list_node));
    if (node) {
        node->prev = NULL;
        node->next = NULL;
        node->data = data;
    }
    return node;
}

struct list *list_create(void) {
    struct list *list = malloc(sizeof(struct list));
    if (!list) {
        return list;
    }
    list->first = NULL;
    list->last = NULL;
    list->count = 0;
    return list;
}

size_t list_count(const struct list *list) {
    return list->count;
}

void list_push(struct list *list, ll_data_t item_data) {
    struct list_node *node = list_node_create(item_data);
    if (!node) {
        exit(EXIT_FAILURE);
    }
    if (list->count == 0) {
        list->first = list->last = node;
    } else {
        node->prev = list->last;
        list->last->next = node;
        list->last = node;
    }
    list->count += 1;
}

ll_data_t list_pop(struct list *list) {
    if (list->count == 0) {
        exit(EXIT_FAILURE);
    }
    ll_data_t data = list->last->data;
    if (list->count == 1) {
        free(list->last);
        list->first = list->last = NULL;
    } else {
        list->last = list->last->prev;
        free(list->last->next);
        list->last->next = NULL;
    }
    list->count -= 1;
    return data;
}

void list_unshift(struct list *list, ll_data_t item_data) {
    struct list_node *node = list_node_create(item_data);
    if (!node) {
        exit(EXIT_FAILURE);
    }
    if (list->count == 0) {
        list->first = list->last = node;
    } else {
        node->next = list->first;
        list->first->prev = node;
        list->first = node;
    }
    list->count += 1;
}

ll_data_t list_shift(struct list *list) {
    if (list->count == 0) {
        exit(EXIT_FAILURE);
    }
    ll_data_t data = list->first->data;
    if (list->count == 1) {
        free(list->first);
        list->first = list->last = NULL;
    } else {
        list->first = list->first->next;
        free(list->first->prev);
        list->first->prev = NULL;
    }
    list->count -= 1;
    return data;
}

void list_delete(struct list *list, ll_data_t data) {
    for (struct list_node *p = list->first; p != NULL; p = p->next) {
        if (p->data == data) {
            if (p == list->first) {
                list_shift(list);
            } else if (p == list->last) {
                list_pop(list);
            } else {
                p->prev->next = p->next;
                p->next->prev = p->prev;
                free(p);
                list->count -= 1;
            }
            break;
        }
    }
}

void list_destroy(struct list *list) {
    struct list_node *p = list->first;
    while (p) {
        struct list_node *next = p->next;
        free(p);
        p = next;
    }
    list->first = NULL;
    list->last = NULL;
    list->count = 0;
    free(list);
}
