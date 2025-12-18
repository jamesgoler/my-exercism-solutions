#include "pig_latin.h"
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdbool.h>

static const bool is_vowel[256] = {
    ['a']=true, ['e']=true, ['i']=true, ['o']=true, ['u']=true,
};

static inline size_t count_words(const char *phrase);
static inline void mv2end_append_ay(char *out, const char *in, size_t len, const char *mvend);
static inline void translate_word(char *out, const char *in, size_t len);

static inline size_t count_words(const char *phrase) {
    size_t count = 0;
    bool open_for_new_word = true;
    for (const char *ptr = phrase; *ptr != '\0'; ptr += 1) {
        if (*ptr != ' ' && open_for_new_word) {
            count += 1;
            open_for_new_word = false;
        } else {
            open_for_new_word = true;
        }
    }
    return count;
}

static inline void mv2end_append_ay(char *out, const char *in, size_t len, const char *mvend) {
    strcpy(out, mvend);
    strncpy(out + len - (mvend - in), in, mvend - in);
    strcpy(out + len, "ay");
}

static inline void translate_word(char *out, const char *in, size_t len) {
    const char *ptr = in;
    if (!(is_vowel[(size_t)*in] || strncmp(in, "xr", 2) == 0 || strncmp(in, "yt", 2) == 0)) {
        while (*ptr != '\0' && *ptr != ' ') {
            if (is_vowel[(size_t)*ptr]) {
                break;
            } else if (strncmp(ptr, "qu", 2) == 0) {
                ptr += 2;
                break;
            } else if (*ptr == 'y' && ptr > in) {
                break;
            }
            ptr += 1;
        }
    }
    mv2end_append_ay(out, in, len, ptr);
}

char *translate(const char *phrase) {
    if (!phrase) {
        return NULL;
    }

    size_t len = strlen(phrase);
    char *result = malloc((len + 1 + (2 * count_words(phrase))) * sizeof(char));
    const char *rptr = phrase;
    char *wptr = result;

    while (*rptr != '\0') {
        while (*rptr == ' ') {
            *(wptr++) = *(rptr++);
        }
        if (*rptr == '\0') {
            *wptr = '\0';
            break;
        }
        size_t len = 0;
        for (const char *ptr = rptr; *ptr != '\0' && *ptr != ' '; ptr += 1) {
            len += 1;
        }
        translate_word(wptr, rptr, len);
        wptr += len + 2;
        rptr += len;
    }
    return result;
}
