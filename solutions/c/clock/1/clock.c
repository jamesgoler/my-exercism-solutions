#include "clock.h"

#include <string.h>

static inline int clock_hour(clock_t clock);
static inline int clock_minute(clock_t clock);

static inline int clock_hour(clock_t clock) {
    return (clock.text[0]-'0') * 10 + (clock.text[1]-'0');
}

static inline int clock_minute(clock_t clock) {
    return (clock.text[3]-'0') * 10 + (clock.text[4]-'0');
}

clock_t clock_create(int hour, int minute) {
    hour %= 24;
    hour += minute / 60;
    hour %= 24;
    
    minute %= 60;
    if (minute < 0) {
        minute += 60;
        hour -= 1;
    }
    if (hour < 0) {
        hour += 24;
    }
    
    clock_t c;
    c.text[0] = (hour / 10) + '0';
    c.text[1] = (hour % 10) + '0';
    c.text[2] = ':';
    c.text[3] = (minute / 10) + '0';
    c.text[4] = (minute % 10) + '0';
    c.text[5] = '\0';
    return c;
}

clock_t clock_add(clock_t clock, int minute_add) {
    clock_t tmp = clock_create(0, minute_add);
    int hour = clock_hour(tmp) + clock_hour(clock);
    int minute = clock_minute(tmp) + clock_minute(clock);
    return clock_create(hour, minute);
}

clock_t clock_subtract(clock_t clock, int minute_subtract) {
    return clock_add(clock, -minute_subtract);
}

bool clock_is_equal(clock_t a, clock_t b) {
    return memcmp(&a, &b, sizeof(a)) == 0;
}