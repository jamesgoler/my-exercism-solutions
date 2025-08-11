#include "rna_transcription.h"

#include <string.h>
#include <stdlib.h>

char *to_rna(const char * restrict dna) {
    if (!dna) {
        return NULL;
    }
    
    char * restrict rna = malloc((sizeof(char) * strlen(dna)) + 1);
    if (!rna) {
        return NULL;
    }
    
    const char *dptr = dna;
    char *rptr = rna;
loop_start:
    switch (*dptr++) {
    case 'G':
        *rptr++ = 'C';
        break;
    case 'C':
        *rptr++ = 'G';
        break;
    case 'T':
        *rptr++ = 'A';
        break;
    case 'A':
        *rptr++ = 'U';
        break;
    default:
        goto loop_end;
    }
    goto loop_start;
loop_end:
    *rptr = '\0';

    return rna;
}