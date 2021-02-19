#include <stdio.h>
#include <stdlib.h>
#include <string.h.>


#include "sort_tool.h"


#define ARRAY_SIZE 30

typedef enum {
    AGE_ASCENDING = 0,
    AGE_DESCENDING,
    NAME_ASCENDING,
    NAME_DESCENDING,
    E_END,
} e_sort_order;

void array_print(struct entity* array, size_t size) {
    for (size_t i = 0; i < size; ++i) {
        printf("{%" PRId64 ",%s}, ", array[i].age, array[i].name);
    }
    printf("\n\n");
}

bool pred_age_ascending(struct entity a, struct entity b) {
    return a.age >= b.age;
}

bool pred_age_descending(struct entity a, struct entity b) {
    return a.age <= b.age;
}

bool pred_name_ascending(struct entity a, struct entity b) {
    return (strcmp((a.name), (b.name)) >= 0);
}

bool pred_name_descending(struct entity a, struct entity b) {
    return (strcmp((a.name), (b.name)) <= 0);
}

const char* str_gen() {
    int64_t a = rand() % 4;
    if (a == 3) {
        return "aba";
    } else if (a == 2) {
        return "we";
    } else if (a == 1) {
        return "fanfic";
    } else {
        return "kicks";
    }
}

int main(void) {
    struct entity arr[ARRAY_SIZE];
    predicate pfa[E_END] = {[AGE_ASCENDING] = &pred_age_ascending,
                            [AGE_DESCENDING] = &pred_age_descending,
                            [NAME_ASCENDING] = &pred_name_ascending,
                            [NAME_DESCENDING] = &pred_name_descending
    };




    for (size_t i = 0; i < ARRAY_SIZE; ++i) {
        arr[i] = (struct entity) {.age = (const int64_t)(rand() % 1000), .name = (const char*) str_gen()};
    }

    array_print(arr, ARRAY_SIZE);
    int_bubble_sort(arr, ARRAY_SIZE, pfa[AGE_ASCENDING]);
    array_print(arr, ARRAY_SIZE);
    int_bubble_sort(arr, ARRAY_SIZE, pfa[AGE_DESCENDING]);
    array_print(arr, ARRAY_SIZE);
    int_bubble_sort(arr, ARRAY_SIZE, pfa[NAME_ASCENDING]);
    array_print(arr, ARRAY_SIZE);
    int_bubble_sort(arr, ARRAY_SIZE, pfa[NAME_DESCENDING]);
    array_print(arr, ARRAY_SIZE);
}
