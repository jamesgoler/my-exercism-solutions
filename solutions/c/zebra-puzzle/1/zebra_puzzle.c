#include "zebra_puzzle.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

enum HouseKey {
    COLOR,
    NATIONALITY,
    PET,
    BEVERAGE,
    HOBBY,
    KEY_NUM,
};

enum HouseValue {
    UNKNOWN,
    RED, GREEN, BLUE, IVORY, YELLOW,
    NORWEGIAN, ENGLISHMAN, SPANIARD, UKRAINIAN, JAPANESE,
    HORSE, ZEBRA, DOG, SNAIL, FOX,
    COFFEE, MILK, WATER, TEA, JUICE,
    PAINTING, CHESS, DANCING, READING, FOOTBALL,
    VALUE_NUM,
};

struct house {
    enum HouseValue values[KEY_NUM];
};

static inline struct house create_house(enum HouseValue color, enum HouseValue nationality, enum HouseValue pet, enum HouseValue beverage, enum HouseValue hobby);
static inline bool can_merge(struct house *h1, struct house *h2);
static inline void merge(struct house *h1, struct house *h2);
static inline void undo_merge(struct house *h1, struct house *h2);
static inline const char *nationality_to_string(enum HouseValue v);
static bool solve_dfs(struct house *houses, size_t house_num, struct house *statements, size_t statement_num, size_t nth);

static inline struct house create_house(enum HouseValue color, enum HouseValue nationality, enum HouseValue pet, enum HouseValue beverage, enum HouseValue hobby) {
    return (struct house) {
        .values = { color, nationality, pet, beverage, hobby }
    };
}

static inline bool can_merge(struct house *h1, struct house *h2) {
    for (int i = 0; i < KEY_NUM; i += 1) {
        if (h1->values[i] != UNKNOWN && h2->values[i] != UNKNOWN && h1->values[i] != h2->values[i]) {
            return false;
        }
    }
    return true;
}

static inline void merge(struct house *h1, struct house *h2) {
    for (int i = 0; i < KEY_NUM; i += 1) {
        h1->values[i] |= h2->values[i];
    }
}

static inline void undo_merge(struct house *h1, struct house *h2) {
    for (int i = 0; i < KEY_NUM; i += 1) {
        if (h2->values[i] != UNKNOWN) {
            h1->values[i] = UNKNOWN;
        }
    }
}

static inline const char *nationality_to_string(enum HouseValue v) {
    switch (v) {
        case NORWEGIAN:
            return "Norwegian";
        case ENGLISHMAN:
            return "Englishman";
        case SPANIARD:
            return "Spaniard";
        case UKRAINIAN:
            return "Ukrainian";
        case JAPANESE:
            return "Japanese";
        default:
            return "";
    }
}

static bool solve_dfs(struct house *houses, size_t house_num, struct house *statements, size_t statement_num, size_t nth) {
    if (nth == statement_num) {
        for (size_t i = 0; i < house_num; i += 1) {
            if (houses[i].values[COLOR] == GREEN) {
                if (i == 0 || houses[i-1].values[COLOR] != IVORY) {
                    return false;
                }
            } else if (houses[i].values[COLOR] == YELLOW) {
                if ((i == 0 && houses[1].values[PET] != HORSE) ||
                    (i == house_num-1 && houses[house_num-2].values[PET] != HORSE) ||
                    (houses[i-1].values[PET] != HORSE && houses[i+1].values[PET] != HORSE)) {
                    return false;
                }
            }
            if (houses[i].values[HOBBY] == READING) {
                if ((i == 0 && houses[1].values[PET] != FOX) ||
                    (i == house_num-1 && houses[house_num-2].values[PET] != FOX) ||
                    (houses[i-1].values[PET] != FOX && houses[i+1].values[PET] != FOX)) {
                    return false;
                }
            } 
        }
        return true;
    }
    for (size_t i = 0; i < house_num; i += 1) {
        if (can_merge(&houses[i], &statements[nth])) {
            merge(&houses[i], &statements[nth]);
            if (solve_dfs(houses, house_num, statements, statement_num, nth + 1)) {
                return true;
            }
            undo_merge(&houses[i], &statements[nth]);
        }
    }
    return false;
}

solution_t solve_puzzle(void) {
    struct house houses[] = {
        create_house(UNKNOWN, NORWEGIAN, UNKNOWN, UNKNOWN, UNKNOWN),
        create_house(BLUE,    UNKNOWN,   UNKNOWN, UNKNOWN, UNKNOWN),
        create_house(UNKNOWN, UNKNOWN,   UNKNOWN, MILK,    UNKNOWN),
        create_house(UNKNOWN, UNKNOWN,   UNKNOWN, UNKNOWN, UNKNOWN),
        create_house(UNKNOWN, UNKNOWN,   UNKNOWN, UNKNOWN, UNKNOWN),
    };
    struct house statements[] = {
        create_house(RED,     ENGLISHMAN, UNKNOWN, UNKNOWN, UNKNOWN),
        create_house(IVORY,   UNKNOWN,    UNKNOWN, UNKNOWN, UNKNOWN),
        create_house(GREEN,   UNKNOWN,    UNKNOWN, COFFEE,  UNKNOWN), // the right of the ivory house.
        create_house(YELLOW,  UNKNOWN,    UNKNOWN, UNKNOWN, PAINTING), // next to the house with the horse.
        create_house(UNKNOWN, UNKNOWN,    HORSE,   UNKNOWN, UNKNOWN),
        create_house(UNKNOWN, UNKNOWN,    UNKNOWN, WATER,   UNKNOWN),
        create_house(UNKNOWN, UNKNOWN,    ZEBRA,   UNKNOWN, UNKNOWN),
        create_house(UNKNOWN, SPANIARD,   DOG,     UNKNOWN, UNKNOWN),
        create_house(UNKNOWN, UKRAINIAN,  UNKNOWN, TEA,     UNKNOWN),
        create_house(UNKNOWN, JAPANESE,   UNKNOWN, UNKNOWN, CHESS),
        create_house(UNKNOWN, UNKNOWN,    SNAIL,   UNKNOWN, DANCING),
        create_house(UNKNOWN, UNKNOWN,    UNKNOWN, UNKNOWN, READING), // next to the person with the fox.",
        create_house(UNKNOWN, UNKNOWN,    FOX,     UNKNOWN, UNKNOWN),
        create_house(UNKNOWN, UNKNOWN,    UNKNOWN, JUICE,   FOOTBALL),
    };

    const size_t house_num = 5;
    const size_t statement_num = 14;

    if (!solve_dfs(houses, house_num, statements, statement_num, 0)) {
        fprintf(stderr, "Unable to solve the problem.");
        exit(EXIT_FAILURE);
    }

    solution_t sol;
    for (size_t i = 0; i < house_num; i += 1) {
        if (houses[i].values[BEVERAGE] == WATER) {
            sol.drinks_water = nationality_to_string(houses[i].values[NATIONALITY]);
        }
        if (houses[i].values[PET] == ZEBRA) {
            sol.owns_zebra = nationality_to_string(houses[i].values[NATIONALITY]);
        }
    }
    return sol;
}