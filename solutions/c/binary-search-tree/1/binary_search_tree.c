#include "binary_search_tree.h"

#include <stddef.h>
#include <stdbool.h>
#include <stdlib.h>

static inline struct node *create_node(int data);
static inline struct node *insert_tree(node_t *tree, int data);
static inline size_t count_nodes(node_t *tree);
static inline void fill_sorted_data(node_t *tree, int *result, size_t *len);

static inline struct node *create_node(int data) {
    struct node *node = malloc(sizeof(struct node));
    node->right = NULL;
    node->left = NULL;
    node->data = data;
    return node;
}

static inline node_t *insert_tree(node_t *tree, int data) {
    struct node *node = create_node(data);

    if (!tree) {
        return node;
    }
    struct node *last = NULL;
    struct node *ptr = tree;
    bool go_left = true;
    while (ptr != NULL) {
        last = ptr;
        go_left = data <= ptr->data;
        ptr = go_left ? ptr->left : ptr->right;
    }
    if (go_left) {
        last->left = node;
    } else {
        last->right = node;
    }
    return tree;
}

static inline size_t count_nodes(node_t *tree) {
    if (!tree) {
        return 0;
    }
    return count_nodes(tree->left) + count_nodes(tree->right) + 1;
}

static inline void fill_sorted_data(node_t *tree, int *result, size_t *len) {
    if (!tree) {
        return;
    }
    fill_sorted_data(tree->left, result, len);
    result[*len] = tree->data;
    *len += 1;
    fill_sorted_data(tree->right, result, len);
}

node_t *build_tree(int *tree_data, size_t tree_data_len) {
    node_t *root = NULL;
    for (size_t i = 0; i < tree_data_len; i += 1) {
        root = insert_tree(root, tree_data[i]);
    }
    return root;
}

void free_tree(node_t *tree) {
    if (!tree) {
        return;
    }
    free_tree(tree->left);
    free_tree(tree->right);
    free(tree);
}

int *sorted_data(node_t *tree) {
    size_t cap = count_nodes(tree);
    size_t len = 0;

    int *result = malloc(cap * sizeof(int));
    if (!result) {
        return NULL;
    }
    fill_sorted_data(tree, result, &len);
    return result;
}