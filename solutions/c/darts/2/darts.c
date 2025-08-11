#include "darts.h"

#include <math.h>
#include <stdint.h>

uint8_t score(coordinate_t landing_position) {
    // the outer circle has a radius of 10 units
    // the middle circle a radius of 5 units
    // the inner circle a radius of 1.

    double r = hypot(landing_position.x, landing_position.y);
    if (r <= 1.0) {
        return 10;
    }
    if (r <= 5.0) {
        return 5;
    }
    if (r <= 10.0) {
        return 1;
    }
    return 0;
}