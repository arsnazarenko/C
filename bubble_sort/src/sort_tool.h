#ifndef SORT_TOOL_H
#define SORT_TOOL_H
#include <inttypes.h>
#include <stdbool.h>


struct entity {
    int64_t age;
    const char* name;
};

typedef bool (*predicate)(struct entity, struct entity);

void int_bubble_sort(struct entity* , size_t, predicate);


#endif