#include<inttypes.h>
#include<stdio.h>
#include<stdlib.h>


#define LIMIT 6

size_t count_gt(uint16_t* array, size_t size) {
    size_t count = 0;
    for (size_t i = 0; i < size; i++) {
        if (*(array + i) > LIMIT ) {
            count++;
        }
    }
    return count;
}

int main(int argc, char* argv[]) {
    size_t N = 8 * 1024 * 1024;
    uint16_t* arr = malloc(sizeof(uint16_t) * N);
    if (arr == NULL) {
        return 1;
    }
    for (size_t j = 0; j < N; j++) {
        *(arr + j) = 9;
        printf("%" PRIu16,  *(arr + j));
    }

    size_t result = count_gt(arr, N);

    printf("Ответ: %" PRId64, result);

    return 0;

}
