#include<inttypes.h>
#include<stdio.h>


void types_io();

int main(int argc, char* argv[]) {
    types_io();

    return 0;
}

void types_io() {

    /*
         char - численный тип с постоянным размером 1 байт
         в языке Си используется для отображения ASCII символов
         для большинства компиляторов по умолчанию char - signed char
    */
    char number = 5;
    char symbol_code = 'x';
    char null_terminator = '\0';
    
    /* может быть signed - знаковый */
    signed char unumber = -2;

    
    /* может быть unsigned - беззнаковый */
    unsigned char ch = 4;

    /*
        Но стандарт С99 ввел новые ПЛАТФОРМОНЕЗАВИСИМЫЕ int типы.
        В этих типах явно указан рамер и знаковость
        Эти типы определены в заголовочном файле stdint.h
    */

    /* знаковые  8, 16, 32, 64 - разрядные int */
    
    int16_t i16 = -100;
    int32_t i32 = -1000;
    int64_t i64 = -100000;

    /* По аналогии беззнаковые  */
    uint8_t u8 = 52;
    uint16_t u16 = 103;
    uint32_t u32 = 1300;
    uint64_t u64 = 100300;
    
    /*
         Теперь предстоит разобраться с выводом и вводом
         данных таких типов
    */

    /* Конкатенация строковых литералов */
    printf("Hello" "world\n");

    #define WORLD "beautiful world"
    printf("Hello, " WORLD "!\n");



    /*
        Обязательно включение файла <inttypes.h>
        Инструкция:
        * PRI или SCN (вывод или ввод)
        * Формат: x (16-ричный), u (беззнаковый), i или d (знаковый)
        * Размер в битах или PTR для указателей
    */

    printf( "Signed 64-bit integer: %" PRId64 "\n", i64);
    printf( "Unsigned 32-bit integer: %" PRIu32 "\n", u32);
    printf( "Pointer, hexadecima    %" PRIxPTR "\n", &i64 );

    scanf("%" SCNd64, &i64 );
    scanf("%" SCNu64, &u64 );
    
}



