#include "triangle.h"

static inline bool is_triangle(triangle_t sides);

bool is_equilateral(triangle_t sides) {
    return is_triangle(sides) && ((sides.a == sides.b) && (sides.b == sides.c));
}

bool is_isosceles(triangle_t sides) {
    return is_triangle(sides) && ((sides.a == sides.b) || (sides.b == sides.c) || (sides.a == sides.c));
}

bool is_scalene(triangle_t sides) {
    return is_triangle(sides) && ((sides.a != sides.b) && (sides.b != sides.c) && (sides.a != sides.c));
}

static inline bool is_triangle(triangle_t sides) {
    return (sides.a < sides.b + sides.c) && (sides.b < sides.a + sides.c) && (sides.c < sides.a + sides.b);
}
