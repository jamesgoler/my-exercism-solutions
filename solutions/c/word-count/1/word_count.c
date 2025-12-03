#include "word_count.h"
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

static inline int insert_word(word_count_word_t *words, int num, const char *word);
static inline int search_word(word_count_word_t *words, int num, const char *word, bool *found);

static inline int insert_word(word_count_word_t *words, int num, const char *word) {
    bool found = false;
    int pos = search_word(words, num, word, &found);
    if (found) {
        words[pos].count += 1;
        return num;
    }
    if (num == MAX_WORDS) {
        return EXCESSIVE_NUMBER_OF_WORDS;
    }
    memmove(&words[pos + 1], &words[pos], sizeof(word_count_word_t) * (num - pos));
    strcpy(words[pos].text, word);
    words[pos].count = 1;
    return num + 1;
}

static inline int search_word(word_count_word_t *words, int num, const char *word, bool *found) {
    int l = 0;
    int r = num;

    while (l < r) {
        int m = l + ((r-l)>>1);
        int d = strcmp(words[m].text, word);
        if (d == 0) {
            *found = true;
            return m;
        } else if (d > 0) {
            r = m;
        } else {
            l = m + 1;
        }
    }
    *found = false;
    return l;
}

int count_words(const char *sentence, word_count_word_t *words) {
    if (!sentence || !words) {
        return 0;
    }

    int num = 0;

    char buf[MAX_WORD_LENGTH + 1];
    size_t word_len = 0;

    for (const char *ptr = sentence; *ptr != '\0'; ptr += 1) {
        if (isalnum(*ptr) || (word_len > 0 && *ptr == '\'' && isalnum(*(ptr + 1)))) {
            buf[word_len++] = tolower(*ptr);
            if (word_len > MAX_WORD_LENGTH) {
                return EXCESSIVE_LENGTH_WORD;
            }
        } else if (word_len > 0) {
            buf[word_len] = '\0';
            num = insert_word(words, num, buf);
            if (num < 0) {
                return num;
            }
            word_len = 0;
        }
    }
    if (word_len > 0) {
        buf[word_len] = '\0';
        num = insert_word(words, num, buf);
    }
    return num;
}

