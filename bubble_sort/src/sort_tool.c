#include "sort_tool.h"


void int_bubble_sort(struct entity* array, size_t size, predicate pf) {
    for (size_t i = 1; i < size; ++i) {
        for (size_t j = 0; j < size - 1; ++j) {
            if (pf(array[j], array[j+1])) {
                struct entity tmp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = tmp;
            }
        }
    }
}