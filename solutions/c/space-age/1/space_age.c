#include "space_age.h"

static const int64_t SECONDS_PER_YEAR_EARTH = 31557600;

static const float SECONDS_PER_YEAR[] = {
    SECONDS_PER_YEAR_EARTH * 0.2408467,
    SECONDS_PER_YEAR_EARTH * 0.61519726,
    SECONDS_PER_YEAR_EARTH,
    SECONDS_PER_YEAR_EARTH * 1.8808158,
    SECONDS_PER_YEAR_EARTH * 11.862615,
    SECONDS_PER_YEAR_EARTH * 29.447498,
    SECONDS_PER_YEAR_EARTH * 84.016846,
    SECONDS_PER_YEAR_EARTH * 164.79132,
};

float age(planet_t planet, int64_t seconds) {
    if (planet <= PLANET_ERROR || planet >= PLANET_NUM) {
        return PLANET_ERROR;
    }
    return seconds / SECONDS_PER_YEAR[planet];
}