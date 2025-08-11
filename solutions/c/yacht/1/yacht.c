#include "yacht.h"

#include <stdbool.h>
#include <stddef.h>

static inline void count(char *counter, dice_t dice);
static inline int count_n(char *counts, int n);
static inline int full_house(char *counts);
static inline int four_of_a_kind(char *counts);
static inline int little_straight(char *counts);
static inline int big_straight(char *counts);
static inline int choice(char *counts);
static inline int yacht(char *counts);

static inline void count(char *counter, dice_t dice) {
    for (size_t i = 1; i <= 6; i += 1) {
        counter[i] = 0;
    }
    for (size_t i = 0; i < 5; i += 1) {
        counter[dice.faces[i]] += 1;
    }
}

static inline int count_n(char *counts, int n) {
    return counts[n] * n;
}

static inline int full_house(char *counts) {
    int sum = 0;
    for (size_t i = 1; i <= 6; i += 1) {
        switch (counts[i]) {
            case 0:
                break;
            case 2:
                sum += i * 2;
                break;
            case 3:
                sum += i * 3;
                break;
            default:
                return 0;
        }
    }
    return sum;
}

static inline int four_of_a_kind(char *counts) {
    for (size_t i = 1; i <= 6; i += 1) {
        if (counts[i] >= 4) {
            return i * 4;
        }
    }
    return 0;
}

static inline int little_straight(char *counts) {
    for (size_t i = 1; i <= 5; i += 1) {
        if (counts[i] != 1) {
            return 0;
        }
    }
    return 30;
}

static inline int big_straight(char *counts) {
    for (size_t i = 2; i <= 6; i += 1) {
        if (counts[i] != 1) {
            return 0;
        }
    }
    return 30;
}

static inline int choice(char *counts) {
    int sum = 0;
    for (size_t i = 1; i <= 6; i += 1) {
        sum += i * counts[i];
    }
    return sum;
}

static inline int yacht(char *counts) {
    for (size_t i = 2; i <= 6; i += 1) {
        if (counts[i] == 5) {
            return 50;
        }
    }
    return 0;
}

int score(dice_t dice, category_t category) {
    char counts[7];
    count(counts, dice);
    
    switch (category) {
        case ONES:
            return count_n(counts, 1);
        case TWOS:
            return count_n(counts, 2);
        case THREES:
            return count_n(counts, 3);
        case FOURS:
            return count_n(counts, 4);
        case FIVES:
            return count_n(counts, 5);
        case SIXES:
            return count_n(counts, 6);
        case FULL_HOUSE:
            return full_house(counts);
        case FOUR_OF_A_KIND:
            return four_of_a_kind(counts);
        case LITTLE_STRAIGHT:
            return little_straight(counts);
        case BIG_STRAIGHT:
            return big_straight(counts);
        case CHOICE:
            return choice(counts);
        case YACHT:
            return yacht(counts);
    }
    return 0;
}

