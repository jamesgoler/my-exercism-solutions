#include "list_ops.h"

#include <stdio.h>
#include <stdlib.h>

static inline list_t *new_empty_list(size_t length);
static inline list_t *new_empty_list(size_t length) {
    list_t *list = malloc(sizeof(list_t) + length * sizeof(list_element_t));
    list->length = length;
    if (!list) {
        perror("Unable to allocate memory for list.");
        exit(EXIT_FAILURE);
    }
    return list;
}

// constructs a new list
list_t *new_list(size_t length, list_element_t elements[]) {
    list_t *list = new_empty_list(length);
    for (size_t i = 0; i < length; i += 1) {
        list->elements[i] = elements[i];
    }
    return list;
}

// append entries to a list and return the new list
list_t *append_list(list_t *list1, list_t *list2) {
    list_t *list = new_empty_list(length_list(list1) + length_list(list2));
    size_t i = 0;
    for (size_t j = 0; j < length_list(list1); j += 1) {
        list->elements[i++] = list1->elements[j];
    }
    for (size_t j = 0; j < length_list(list2); j += 1) {
        list->elements[i++] = list2->elements[j];
    }
    return list;
}

// filter list returning only values that satisfy the filter function
list_t *filter_list(list_t *list, bool (*filter)(list_element_t)) {
    size_t len = 0;
    for (size_t i = 0; i < length_list(list); i += 1) {
        if (filter(list->elements[i])) {
            len += 1;
        }
    }
    list_t *filtered = new_empty_list(len);
    size_t j = 0;
    for (size_t i = 0; i < length_list(list); i += 1) {
        if (filter(list->elements[i])) {
            filtered->elements[j++] = list->elements[i];
        }
    }
    return filtered;
}

// returns the length of the list
size_t length_list(list_t *list) {
    return list->length;
}

// return a list of elements whose values equal the list value transformed by
// the mapping function
list_t *map_list(list_t *list, list_element_t (*map)(list_element_t)) {
    list_t *mapped = new_empty_list(length_list(list));
    for (size_t i = 0; i < length_list(list); i += 1) {
        mapped->elements[i] = map(list->elements[i]);
    }
    return mapped;
}

// folds (reduces) the given list from the left with a function
list_element_t foldl_list(list_t *list, list_element_t initial,
                          list_element_t (*foldl)(list_element_t, list_element_t))
{
    list_element_t accum = initial;
    for (size_t i = 0; i < length_list(list); i += 1) {
        accum = foldl(list->elements[i], accum);
    }
    return accum;
}

// folds (reduces) the given list from the right with a function
list_element_t foldr_list(list_t *list, list_element_t initial,
                          list_element_t (*foldr)(list_element_t, list_element_t))
{
    list_element_t accum = initial;
    for (size_t i = length_list(list); i > 0; i--) {
        accum = foldr(list->elements[i - 1], accum);
    }
    return accum;
}

// reverse the elements of the list
list_t *reverse_list(list_t *list) {
    list_t *rev = new_empty_list(length_list(list));
    for (size_t i = 0; i < length_list(list); i += 1) {
        rev->elements[i] = list->elements[length_list(list) - 1 - i];
    }
    return rev;
}

// destroy the entire list
// list will be a dangling pointer after calling this method on it
void delete_list(list_t *list) {
    free(list);
}
