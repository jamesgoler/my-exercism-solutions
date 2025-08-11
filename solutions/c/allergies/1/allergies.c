#include "allergies.h"

bool is_allergic_to(allergen_t item, int score) {
    return score & (1 << item);
}

allergen_list_t get_allergens(int score) {
    allergen_list_t list;
    list.count = 0;
    
    for (allergen_t item = ALLERGEN_EGGS; item < ALLERGEN_COUNT; item += 1) {
        if (is_allergic_to(item, score)) {
            list.allergens[item] = true;
            list.count += 1;
        } else {
            list.allergens[item] = false;
        }
    }
    return list;
}