#include<stdio.h>
#include<stdlib.h>
#include<inttypes.h>

size_t count_zeroes(const void* data, size_t bytes) {
    size_t count = 0;
    for (size_t j = 0; j < bytes; j++) {
        if ( *(((const int8_t*) data) + j) == 0 ) {
            count++;
        }
    }
    return count;
}


int main(int argc, char* argv[]) {
    const size_t size = 2048; /* Количество элементов массива  */
    const size_t bytes_count = sizeof(int32_t) * size; /* Размер массива в байтах */
    int32_t* array = (int32_t*) malloc(sizeof(int32_t) * size);
    if (array == NULL) {
        printf("OS didn't give memory, exit");
        return 1;
    }

    for (size_t i = 0; i < size; i++) {
        array[i] = 1;
    }

    const uint64_t res = count_zeroes(array, bytes_count);

    printf("Result: %" PRIu64, res);

    return 0;
}
