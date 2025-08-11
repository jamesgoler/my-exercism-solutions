#ifndef RESISTOR_COLOR_TRIO_H
#define RESISTOR_COLOR_TRIO_H

typedef enum  {
    BLACK =0,
    BROWN = 1,
    RED = 2,
    ORANGE = 3,
    YELLOW = 4,
    GREEN = 5,
    BLUE = 6,
    VIOLET = 7,
    GREY = 8,
    WHITE = 9,
} resistor_band_t;

typedef struct {
    short value;
    enum {
        OHMS,
        KILOOHMS,
        MEGAOHMS,
        GIGAOHMS,
    } unit;
} resistor_value_t;

resistor_value_t color_code(const resistor_band_t *);

#endif
