#include "eliuds_eggs.h"



unsigned int egg_count(unsigned int coop) {
    unsigned int eggs = 0;
    while (coop > 0) {
        if (coop & 1) {
            eggs += 1;
        }
        coop >>= 1;
    }
    return eggs;
}