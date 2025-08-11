#include "anagram.h"

#include <string.h>
#include <ctype.h>
#include <stdbool.h>

static inline enum anagram_status is_anagram(const char *a, const char *b);
static inline bool is_eq_case_insensitive(const char *a, const char *b);
static inline void count_alphabets(size_t counter[26], const char *a);

static inline enum anagram_status is_anagram(const char *a, const char *b) {
    if (is_eq_case_insensitive(a, b)) {
        return NOT_ANAGRAM;
    }
    
    size_t acount[26] = {0};
    size_t bcount[26] = {0};
    count_alphabets(acount, a);
    count_alphabets(bcount, b);

    if (memcmp(acount, bcount, sizeof(acount)) == 0) {
        return IS_ANAGRAM;
    } else {
        return NOT_ANAGRAM;
    }
}

static inline bool is_eq_case_insensitive(const char *a, const char *b) {
    while (*a != '\0' && *b != '\0' && tolower(*a) == tolower(*b)) {
        a += 1;
        b += 1;
    }
    return *a == *b;
}

static inline void count_alphabets(size_t counter[26], const char *a) {
    for (const char *ptr = a; *ptr != '\0'; ptr += 1) {
        counter[tolower(*ptr) - 'a'] += 1;
    }
}

/**
 * @description - determines if any of the words in candidate are anagrams
 *                for subject. Contents of candidate structures may be modified.
 */
void find_anagrams(const char *subject, struct candidates *candidates) {
    for (size_t i = 0; i < candidates->count; i += 1) {
        struct candidate *c = &candidates->candidate[i];
        c->is_anagram = is_anagram(subject, c->word);
    }
}
