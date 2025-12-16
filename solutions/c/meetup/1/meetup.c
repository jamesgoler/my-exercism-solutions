#include "meetup.h"
#include <time.h>
#include <string.h>
#include <stdbool.h>

static inline bool is_leap_year(unsigned int year);
static inline int str2wday(const char *day_of_week);
static inline int last_day_of(unsigned int year, unsigned int month);
static inline int wday_of(unsigned int year, unsigned int month, unsigned int day);

static inline bool is_leap_year(unsigned int year) {
    return year % 4 == 0 && (year % 100 != 0 || year % 400 == 0);
}

static inline int str2wday(const char *day_of_week) {
    const char *weekdays[] = {
        "Sunday",
        "Monday",
        "Tuesday",
        "Wednesday",
        "Thursday",
        "Friday",
        "Saturday"
    };

    for (int i = 0; i < 7; i += 1) {
        if (strcmp(weekdays[i], day_of_week) == 0) {
            return i;
        }
    }
    return -1;
}

static inline int last_day_of(unsigned int year, unsigned int month) {
    switch (month) {
        case 2:
            return is_leap_year(year) ? 29 : 28;
        case 1:
        case 3:
        case 5:
        case 7:
        case 8:
        case 10:
        case 12:
            return 31;
        default:
            return 30;
    }
}

static inline int wday_of(unsigned int year, unsigned int month, unsigned int day) {
    struct tm t = {0};
    t.tm_year = year - 1900;
    t.tm_mon = month - 1;
    t.tm_mday = day;
    mktime(&t);
    return t.tm_wday;
}

int meetup_day_of_month(unsigned int year, unsigned int month, const char *week, const char *day_of_week) {
    int mday = 1;
    int wday_of_first_day = wday_of(year, month, mday);
    int last_day = last_day_of(year, month);
    int expected_wday = str2wday(day_of_week);
    if (expected_wday < 0) {
        return -1;
    }

    mday += (expected_wday - wday_of_first_day + 7) % 7;

    if (strcmp(week, "first") == 0) {
        return mday;
    }
    if (strcmp(week, "second") == 0) {
        return mday + 7;
    }
    if (strcmp(week, "third") == 0) {
        return mday + 14;
    }
    if (strcmp(week, "fourth") == 0) {
        return mday + 21;
    }
    if (strcmp(week, "last") == 0) {
        return (mday + 28 <= last_day) ? mday + 28 : mday + 21;
    }
    if (strcmp(week, "teenth") == 0) {
        while (mday < 13) {
            mday += 7;
        }
        return mday;
    }
    return -1;
}
