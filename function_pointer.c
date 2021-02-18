#include <inttypes.h>
#include <stdio.h>
//----------Указатели на функции-------------------

int64_t square(int64_t x) {return x * x;}
int64_t cube(int64_t x) {return x * x * x;}
void print_array(const int64_t* array, size_t size) {
    for (size_t i = 0; i < size; ++i) {
        printf("%" PRId64 " ", array[i]);
    }
    printf("\n");
}
void map(int64_t* array, size_t size, int64_t (*fn)(int64_t)) {
    for (size_t i = 0; i < size; ++i) {
        array[i] = (*fn)(array[i]);
    }
}


int main(int argc, char** argv) {
    int64_t array[] = {1, 2, 3, 4, 5};
    const size_t count = sizeof(array) / sizeof(int64_t);
    print_array(array, count);

    //  указатель на функцию int64_t -> int64_t
    //
    //  Объявление указателя:
    //  <возвр. значение> (*<имя переменной указателя>) (<аргументы>)
    //
    //  &<имя_готовой_функции> - получение указателя определенной функции
    int64_t (*mapper)(int64_t) = &square;


    for (size_t i = 0; i < count; ++i) {

        //  вызов функции через указатель:
        //  (*<имя указателя>)
        array[i] = (*mapper)(array[i]);
    }
    print_array(array, count);


    //  Переменная типа указателя на функцию позволяет вызывать через себя то одну функцию, то другую.
    //  Для этого достаточно изменить её значение:
    mapper = &cube;
    for (size_t j = 0; j < count; ++j) {
        array[j] = (*mapper)(array[j]);
    }


    print_array(array, count);
    return 0;
}