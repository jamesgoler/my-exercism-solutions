#include "dnd_character.h"

#include <time.h>
#include <stdlib.h>

int ability(void) {
    static int seeded = 0;
    if (seeded == 0) {
        srand(time(NULL));
    }
    int min = 0;
    int sum = 0;
    for (int i = 0; i < 4; i += 1) {
        int d = rand() % 6 + 1;
        if (min < d) {
            min = d;
        }
        sum += d;
    }
    sum -= min;
    return sum;
}

int modifier(int score) {
    score -= 10;
    if (score < 0) {
        score -= 1;
    }
    return score / 2;
}

dnd_character_t make_dnd_character(void) {
    dnd_character_t ch = (dnd_character_t) {
        .strength = ability(),
        .dexterity = ability(),
        .constitution = ability(),
        .intelligence = ability(),
        .wisdom = ability(),
        .charisma = ability(),
    };
    ch.hitpoints = 10 + modifier(ch.constitution);
    return ch;
}
