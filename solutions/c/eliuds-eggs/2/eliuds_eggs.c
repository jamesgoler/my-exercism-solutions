#include "eliuds_eggs.h"

unsigned int egg_count(unsigned int coop) {
    return __builtin_popcount(coop);
}