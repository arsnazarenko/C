#include <stdio.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdlib.h>

//  оболочка над элементом массива
struct maybe_int64 {
    bool valid;
    int64_t value;
};

const struct maybe_int64 none_int64 = { 0 };

struct maybe_int64 just_int64( int64_t i ) {
    return (struct maybe_int64) { .value = i, .valid = true };
}

//  структура подмассива
struct array_int {
    size_t size;
    int64_t* data;
};

//  оболочка над структурой подмассива
struct maybe_array_int {
    struct array_int value;
    bool valid;
};

struct maybe_array_int some_array_int(struct array_int array) {
    return (struct maybe_array_int) { .value = array, .valid = true };
}

const struct maybe_array_int none_array_int = { .value = {.data = NULL, .size = 0}, .valid = false };

//структура двумерного массива
struct array_array_int {
    struct array_int* data;
    size_t size;
};

size_t read_size() { size_t sz = 0; scanf("%zu", &sz); return sz; }

int64_t read_int64() { int64_t a; scanf("%"SCNd64, &a); return a; }

void array_int_fill( int64_t* array, size_t sz ) {
    for( size_t i = 0; i < sz; i = i + 1 ) {
        array[i] = read_int64();
    }
}

struct array_int array_int_read() {
    const size_t size = read_size();
    if (size > 0) {
        int64_t* array = (int64_t*) malloc( sizeof(int64_t) * size);
        array_int_fill( array, size );
        return (struct array_int) { .data = array, .size = size };
    }
    else return (struct array_int) {0};
}

// возвращает ошибку если индекс за пределами массива
struct maybe_int64 array_int_get( struct array_int a, size_t i ) {
    if (i > 0 || i < a.size) {
        return just_int64(a.data[i]);
    }
    return just_int64(a.data[i]);
}

// возвращает false если индекс за пределами массива
bool array_int_set( struct array_int a, size_t i, int64_t value ) {
    if (i > 0 || i < a.size) {
        a.data[i] = value;
        return true;
    }
    return false;
}

void array_int_print( struct array_int array ) {
    for (size_t i = 0; i < array.size; i = i + 1) {
        printf("%" PRId64 " " , array_int_get( array, i).value);
    }
}


struct maybe_int64 array_int_min( struct array_int array ) {
    if (array.size > 0) {
        struct maybe_int64 min = array_int_get(array, 0);
        for (size_t i = 1; i < array.size; ++i) {
            struct maybe_int64 tmp = array_int_get(array, i);
            if (tmp.value < min.value) {
                min = tmp;
            }
        }
        return min;
    }
    return none_int64;
}

void array_int_free( struct array_int a ) {
    if ( a.size > 0 ) {
        free((void*) a.data);
        a.size = 0;
    }
}

void array_int_normalize( struct array_int array, int64_t m ) {
    for (size_t i = 0; i < array.size; i = i + 1) {
        array.data[i] = array.data[i] - m;
    }
}

struct maybe_array_int array_array_int_get_row( struct array_array_int a, size_t i ) {
    if ( 0 <= i && i < a.size ) { return some_array_int( a.data[i] ); }
    else { return none_array_int; }
}

bool array_array_int_set_row( struct array_array_int a, size_t i, struct array_int value ) {
    if (0 <= i && i < a.size) {
        a.data[i] = value;
        return true;
    }
    else { return false; }
}

struct maybe_int64 array_array_int_get( struct array_array_int a, size_t i, size_t j ) {
    struct maybe_array_int row = array_array_int_get_row(a, i);
    if (row.valid == true) {
        struct array_int cur_row = row.value;
        struct maybe_int64 result = array_int_get(cur_row, j);
        return result;
    }
    return none_int64;
}

bool array_array_int_set( struct array_array_int a, size_t i, size_t j, int64_t value ) {
    struct maybe_array_int row = array_array_int_get_row(a, i);
    if (row.valid == true) {
        struct array_int cur_row = row.value;
        if (array_int_set(cur_row, j, value)) {
            return array_array_int_set_row( a, i, cur_row);
        }
    }
    return false;

}

struct maybe_int64 maybe_int64_min(struct maybe_int64 a, struct maybe_int64 b) {
    if (!a.valid && !b.valid) {
        return none_int64;
    } else if (!a.valid) {
        return b;
    } else if (!b.valid) {
        return a;
    } else if (a.value < b.value) {
        return a;
    } else {
        return b;
    }
}

struct maybe_int64 array_array_int_min( struct array_array_int array ) {
    struct maybe_int64 min = none_int64;
    for (size_t i = 0; i < array.size; ++i) {
        min = maybe_int64_min(min, array_int_min(array.data[i]));
    }
    return min;
}

struct array_array_int array_array_int_read() {
    const size_t rows = read_size();
    if (rows > 0) {
        struct array_int* data = (struct array_int*) malloc(sizeof(struct array_int) * rows);
        for (size_t i = 0; i < rows; ++i) {
            data[i] = array_int_read();
        }
        return (struct array_array_int) {.size = rows, .data = data};
    }
    return (struct array_array_int) {0};
}

void array_array_int_print( struct array_array_int array) {
    for (size_t i = 0; i < array.size; ++i) {
        array_int_print(array.data[i]);
        printf("\n");
    }
}

// вычесть из всех элементов массива массивов число m
void array_array_int_normalize( struct array_array_int array, int64_t m) {
    for (size_t i = 0; i < array.size; i = i + 1) {
        const struct maybe_array_int cur_row = array_array_int_get_row( array, i );
        if (cur_row.valid) {
            array_int_normalize( cur_row.value, m );
        }
    }
}

void array_array_int_free( struct array_array_int array ) {
    for (size_t i = 0; i < array.size; ++i) {
        array_int_free(array.data[i]);
    }
    free((void*) array.data);
    array.size = 0;
}



void perform() {
    struct array_array_int array = array_array_int_read();
    struct maybe_int64 m = array_array_int_min( array );
    if (m.valid) {
        array_array_int_normalize( array, m.value );
        array_array_int_print( array );
    }
    array_array_int_free( array );
}

int main(int argc, char* argv[]) {
    perform()
}