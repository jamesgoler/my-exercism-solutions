#include "darts.h"

#include <math.h>
#include <stdint.h>

uint8_t score(coordinate_t landing_position) {
    // the outer circle has a radius of 10 units
    // the middle circle a radius of 5 units
    // the inner circle a radius of 1.

    double r = sqrt(pow(landing_position.x, 2) + pow(landing_position.y, 2));
    if (r <= 1) {
        return 10;
    }
    if (r <= 5) {
        return 5;
    }
    if (r <= 10) {
        return 1;
    }
    return 0;
}