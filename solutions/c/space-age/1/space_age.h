#ifndef SPACE_AGE_H
#define SPACE_AGE_H

#include <stdint.h>

typedef enum planet {
    PLANET_ERROR = -1,
    MERCURY,
    VENUS,
    EARTH,
    MARS,
    JUPITER,
    SATURN,
    URANUS,
    NEPTUNE,
    PLANET_NUM,
} planet_t;

float age(planet_t planet, int64_t seconds);

#endif
