#include "grade_school.h"

#include <string.h>

static inline int student_cmp(const student_t *a, const student_t *b);
static inline bool exist(const roster_t *roster, const student_t *s);

static inline int student_cmp(const student_t *a, const student_t *b) {
    if (a->grade == b->grade) {
        return strcmp(a->name, b->name);
    } else {
        return a->grade - b->grade;
    }
}

static inline bool exist(const roster_t *roster, const student_t *s) {
    for (size_t i = 0; i < roster->count; i += 1) {
        if (strcmp(roster->students[i].name, s->name) == 0) {
            return true;
        }
    }
    return false;
}

void init_roster(roster_t *roster) {
    roster->count = 0;
}

bool add_student(roster_t *roster, char *name, uint8_t grade) {
    size_t l = 0;
    size_t r = roster->count;

    student_t s;
    s.grade = grade;
    strcpy(s.name, name);

    if (exist(roster, &s)) {
        return false;
    }

    while (l < r) {
        size_t m = l + ((r-l) / 2);
        int d = student_cmp(&roster->students[m], &s);
        if (d == 0) {
            return false;
        }
        if (d < 0) {
            l = m + 1;
        } else {
            r = m;
        }
    }
    for (size_t i = roster->count; i > l; i -= 1) {
        roster->students[i] = roster->students[i - 1];
    }
    roster->students[l] = s;
    roster->count += 1;
    return true;
}

roster_t get_grade(roster_t *roster, uint8_t grade) {
    roster_t result;
    init_roster(&result);
    for (size_t i = 0; i < roster->count; i += 1) {
        if (roster->students[i].grade == grade) {
            result.students[result.count++] = roster->students[i];
        }
    }
    return result;
}
