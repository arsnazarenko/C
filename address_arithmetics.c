#include<stdio.h>
#include<inttypes.h>
int main(int argc, char* argv[]) {
    int32_t A[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
   /*
        Массив в СИ - это константный адрес и область памяти
        Имя массива (A) - указатель на 0 элемент массива
   */
    int32_t* q = A + 7;
    int32_t* p = A + 5; // A + 5 это указатель на ячейку памяти 5 эл. массива
    printf("Через указатель:  %" PRId32 "\n", *(A + 5));
    printf("Стандартно, через индекс :  %" PRId32 "\n", A[5]);

    if (p > q) {
        printf("p > q\n");
    } else {
        printf("p <= q\n");
    }

    printf("q - p = %" PRId8, q - p );
    
    return 0;

}
    
