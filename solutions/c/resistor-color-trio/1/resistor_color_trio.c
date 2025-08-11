#include "resistor_color_trio.h"

#include <math.h>

resistor_value_t color_code(const resistor_band_t *bands) {
    resistor_value_t actual;
    actual.value = (10 * bands[0]) + bands[1];

    if (actual.value == 0) {
        actual.unit = OHMS;
    } else {
        short power = bands[2];
        if (actual.value % 10 == 0) {
            actual.value /= 10;
            power += 1;
        }
        actual.unit = power / 3; // 2 -> 0, 4 -> 1, ...
        actual.value *= (short)pow(10, (power % 3));
    }
    return actual;
}