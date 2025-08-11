#include "darts.h"

#include <math.h>
#include <stdint.h>

uint8_t score(coordinate_t landing_position) {
    float r = hypotf(landing_position.x, landing_position.y);
    if (r <= 1.0F) { // the inner circle
        return 10;
    }
    if (r <= 5.0F) { // the middle circle
        return 5;
    }
    if (r <= 10.0F) { // the outer circle
        return 1;
    }
    return 0;
}