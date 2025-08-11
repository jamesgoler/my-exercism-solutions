#include "protein_translation.h"

#include <stdio.h>

static inline void init_map(amino_acid_t *map);
static inline int hash(const char *const codon);
static inline amino_acid_t get(amino_acid_t *map, const char *const code);
static inline void set(amino_acid_t *map, const char *const code, amino_acid_t value);

static inline void init_map(amino_acid_t *map) {
    for (int i = 0; i < 4 * 4 * 4; i += 1) {
        map[i] = Invalid;
    }
    set(map, "AUG", Methionine);
    set(map, "UUU", Phenylalanine);
    set(map, "UUC", Phenylalanine);
    set(map, "UUA", Leucine);
    set(map, "UUG", Leucine);
    set(map, "UCU", Serine);
    set(map, "UCC", Serine);
    set(map, "UCA", Serine);
    set(map, "UCG", Serine);
    set(map, "UAU", Tyrosine);
    set(map, "UAC", Tyrosine);
    set(map, "UGU", Cysteine);
    set(map, "UGC", Cysteine);
    set(map, "UGG", Tryptophan);
    set(map, "UAA", Stop);
    set(map, "UAG", Stop);
    set(map, "UGA", Stop);
}

static inline int hash(const char *const codon) { // not really.
    int hv = 0;
    for (int i = 0; i < 3; i += 1) {
        int code = 0;
        switch (codon[i]) {
        case 'A':
            code = 0;
            break;
        case 'C':
            code = 1;
            break;
        case 'U':
            code = 2;
            break;
        case 'G':
            code = 3;
            break;
        default:
            return -1;
        }
        hv = (hv << 2) + code;
    }
    return hv;
}

static inline amino_acid_t get(amino_acid_t *map, const char *const code) {
    int i = hash(code);
    return (i > 0) ? map[i] : Invalid;
}

static inline void set(amino_acid_t *map, const char *const code, amino_acid_t value) {
    int i = hash(code);
    if (i > 0) {
        map[i] = value;
    }
}

protein_t protein(const char *const rna) {
    static bool has_init = false;
    static amino_acid_t map[4 * 4 * 4];
    
    if (!has_init) {
        init_map(map);
        has_init = true;
    }
    
    protein_t result;
    result.count = 0;
    result.valid = true;
    
    const char *ptr = rna;
    while (*ptr != '\0') {
        char codon[3];
        for (int i = 0; i < 3; i += 1) {
            if (*ptr == '\0') {
                result.valid = false;
                return result;
            }
            codon[i] = *ptr;
            ptr += 1;
        }
        amino_acid_t b = get(map, codon);
        if (b == Invalid) {
            result.valid = false;
            return result;
        }
        if (b == Stop) {
            break;
        }
        result.amino_acids[result.count++] = b;
    }
    return result;
}
