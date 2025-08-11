#define _GNU_SOURCE
#include "beer_song.h"

#include <string.h>
#include <stdio.h>
#include <ctype.h>

static inline char *bottle2str(uint8_t bottles);
static inline char *stpcpy_capitalize(char *dest, const char *src);
static inline void create_verses(char **song, size_t *line_count, uint8_t bottles);

static inline char *bottle2str(uint8_t bottles) {
    static uint8_t cached_bottles = 99;
    static char bottle_str[16] = "99 bottles";
    if (bottles != cached_bottles) {
        if (bottles == 0) {
            strcpy(bottle_str, "no more bottles");
        } else if (bottles == 1) {
            strcpy(bottle_str, "1 bottle");
        } else {
            sprintf(bottle_str, "%d bottles", bottles);
        }
        cached_bottles = bottles;
    }
    return bottle_str;
}

static inline char *stpcpy_capitalize(char *dest, const char *src) {
    *dest++ = toupper(*src++);
    return stpcpy(dest, src);
}

static inline void create_verses(char **song, size_t *line_count, uint8_t bottles) {
    const char *bottle_str = bottle2str(bottles);
    char buf[128];
    
    char *ptr = stpcpy_capitalize(buf, bottle_str);
    sprintf(ptr, " of beer on the wall, %s of beer.", bottle_str);
    song[(*line_count)++] = strdup(buf);
    
    if (bottles > 0) {
        const char *it_or_one = bottles == 1 ? "it" : "one";
        bottles -= 1;
        bottle2str(bottles);
        sprintf(buf, "Take %s down and pass it around, %s of beer on the wall.", it_or_one, bottle_str);
    } else {
        sprintf(buf, "Go to the store and buy some more, 99 bottles of beer on the wall.");
    }
    song[(*line_count)++] = strdup(buf);
}

void recite(uint8_t start_bottles, uint8_t take_down, char **song) {
    size_t line_count = 0;
    for (uint8_t i = 0; i < take_down; i += 1) {
        create_verses(song, &line_count, start_bottles--);
        if (i < take_down - 1) {
            song[line_count++] = strdup("");
        }
    }
}