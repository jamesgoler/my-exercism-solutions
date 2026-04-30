#include "palindrome_products.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

static inline product_t *create_product();
static inline factor_t *create_factor(int factor_a, int factor_b);
static inline void free_factor(factor_t *f);
static inline bool is_palindrome(int n);

static inline product_t *create_product()
{
    product_t *p = malloc(sizeof(product_t));
    if (!p)
        return NULL;

    *p = (product_t) {
        .factors_sm = NULL,
        .factors_lg = NULL,
    };

    return p;
}

static inline factor_t *create_factor(int factor_a, int factor_b)
{
    factor_t *f = malloc(sizeof(factor_t));
    if (!f)
        return NULL;

    *f = (factor_t) {
      .factor_a = factor_a,
      .factor_b = factor_b,
      .next = NULL,
    };

    return f;
}

static inline void free_factor(factor_t *f)
{
    while (f) {
        factor_t *tmp = f;
        f = f->next;
        free(tmp);
    }
}

static inline bool is_palindrome(int n)
{
    int digits = 1;
    int l = 1;
    for (int tmp = n; tmp >= 10; tmp /= 10) {
        l *= 10;
        digits += 1;
    }
    for (int i = 0; i < digits; i += 2) {
        int leftmost = n / l;
        int rightmost = n % 10;
        if (leftmost != rightmost)
            return false;
        n = (n % l) / 10;
        l /= 100;
    }
    return true;
}

static inline int find_palindrome(int from, int to, factor_t **save_factor, int *save_palindrome)
{
    factor_t *factor = NULL;
    int palindrome = 0;

    const bool find_min = (from <= to);
    const int steps = find_min ? 1 : -1;
    const int end = to + steps;
    for (int i = from; i != end; i += steps) {
        int product = i * i;
        const int product_step = i * steps;
        for (int j = i; j != end; j += steps) {
            if (factor != NULL && product == palindrome) {
                factor_t *tmp = create_factor(i, j);
                if (!tmp)
                    goto exception_enomem;
                tmp->next = factor;
                factor = tmp;
            } else if (factor == NULL || (find_min ? (palindrome > product) : (palindrome < product))) {
                if (is_palindrome(product)) {
                    free_factor(factor);
                    factor_t *tmp = create_factor(i, j);
                    if (!tmp)
                        goto exception_enomem;
                    factor = tmp;
                    palindrome = product;
                }
            } else { // there won't be any better answer.
                break;
            }
            product += product_step;
        }
    }

    *save_factor = factor;
    *save_palindrome = palindrome;
    return 0;

exception_enomem:
    free_factor(factor);
    return -1;
}

product_t *get_palindrome_product(int from, int to)
{
    product_t *p = create_product();
    if (!p)
        goto exception_enomem;

    if (from > to) {
        snprintf(p->error, MAXERR, "invalid input: min is %d and max is %d", from, to);
        return p;
    }

    if (find_palindrome(from, to, &p->factors_sm, &p->smallest) == -1)
        goto exception_enomem;

    if (!p->factors_sm) {
        snprintf(p->error, MAXERR, "no palindrome with factors in the range %d to %d", from, to);
        return p;
    }

    if (find_palindrome(to, from, &p->factors_lg, &p->largest) == -1)
        goto exception_enomem;

    return p;

exception_enomem:
    free_product(p);
    return NULL;
}

void free_product(product_t *p) {
    if (!p)
        return;

    free_factor(p->factors_sm);
    free_factor(p->factors_lg);
    free(p);
}
