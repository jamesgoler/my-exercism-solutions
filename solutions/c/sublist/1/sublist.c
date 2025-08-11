#include "sublist.h"

static inline comparison_result_t check_lists_sl(int *shorter, int *longer, size_t shorter_size, size_t longer_size) {
    size_t i = 0;
    size_t j = 0;
    
    while (i < shorter_size && j < longer_size) {
        if (shorter[i] == longer[j]) {
            i += 1;
        } else {
            j -= i;
            i = 0;
        }
        j += 1;
    }
    if (shorter_size == longer_size && i == shorter_size && j == longer_size) {
        return EQUAL;
    }
    if (i == shorter_size) {
        return SUBLIST;
    }
    return UNEQUAL;
}

comparison_result_t check_lists(int *list_to_compare, int *base_list,
                                size_t list_to_compare_element_count,
                                size_t base_list_element_count) {
    if (list_to_compare_element_count <= base_list_element_count) {
        return check_lists_sl(list_to_compare, base_list, list_to_compare_element_count, base_list_element_count);
    }
    comparison_result_t result = check_lists_sl(base_list, list_to_compare, base_list_element_count, list_to_compare_element_count);
    if (result == SUBLIST) {
        return SUPERLIST;
    } else {
        return result;
    }
}

