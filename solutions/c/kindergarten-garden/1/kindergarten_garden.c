#include "kindergarten_garden.h"

#include <stdlib.h>
#include <string.h>

static inline plant_t get_plant(char code);

static inline plant_t get_plant(char code) {
    switch (code) {
    case 'G': return GRASS;
    case 'C': return CLOVER;
    case 'R': return RADISHES;
    case 'V': return VIOLETS;
    }
    return -1;
}

plants_t plants(const char *diagram, const char *student) {
    size_t row_len = strchr(diagram, '\n') - diagram;
    size_t i = (*student - 'A') << 1;
    size_t j = row_len + 1 + i;

    return (plants_t) {
        .plants = {
            get_plant(*(diagram + i)),
            get_plant(*(diagram + i + 1)),
            get_plant(*(diagram + j)),
            get_plant(*(diagram + j + 1)),
        },
    };
}