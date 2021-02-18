#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>
#include <stdbool.h>


struct point {
    const char *name;
    int64_t x;
    int64_t y;
};

/*
 * В структурах, в отличие от массива,
 * между элементами структур в памяти могут
 * быть пробелы
 * */

/*
 * Это значит, что размер стркутуры может быть больше,
 * чем чем размеров ее элементов
 * Корректный размер вернет только sizeof(struct S)!!
 * */

struct test {       // Минимум один байт пропадёт
    char first[3];  // X X X _
    int64_t second; // X X X X
};                  // X X X X

/*
 * Структуры могут ссылаться на другие структуры через указатели.
 * На структуры того же типа можно только ссылаться,
 * иначе размер структуры был бы бесконечным,
 * ведь в её состав включалась бы она сама.
 * */

struct path {
    const struct point head;
    const struct path* tail;
};

void test(struct point p) {
}

// Есть два случая:
// - или valid = true и value имеет смысл
// - или valid = false и value может быть любым

struct maybe_int64 {
    bool valid;
    int64_t value;
};

// Первый случай; создаем функцию в помощь
// Не бойтесь за производительность
struct maybe_int64 just_int64( int64_t i ) {
    return (struct maybe_int64) { .value = i, .valid = true };
}

// Второй случай; можно создать не функцию,
// а константный экземпляр структуры
// Все поля инициализированы нулями
// .value = 0, .valid = false
const struct maybe_int64 none_int64 = { 0 };

// упакованное число 42 выводится как "Some 42"
// Ошибка выводится как None
void maybe_int64_print( struct maybe_int64 i ) {
    if (i.valid) {
        printf("Some %" PRId64, i.value);
    } else {
        printf("None");
    }
}

// Если обе упаковки содержат ошибку, то результат ошибка
// Если ровно одна упаковка содержит ошибку, то результат -- вторая
// Если обе упаковки содержат число, то результат это минимум из двух чисел.
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




int main(int argc, char *argv[]) {
    struct point p1 = {"p1", 3, 9};

    // Изменение полей
    p1.x = 30;
    p1.y = 90;

    // Создание указателя на стркутуру
    struct point*p1_ptr = &p1;

    struct point p2 = {"p2", 0, 1};
    struct point p3 = {"p3", 2, 2};
    struct point p4 = {"p4", 8, 8};

    const struct path path1 = {p4, NULL};
    const struct path path2 = {p3, &path1};
    const struct path path3 = {p2, &path2};


    // Создание стркутура на ходу
    test((struct point) {"p5", 10, 10});

    // Синтаксис для указания того, какие поля чему равны
    // Остальные поля инициализируются нулевыми значениями
    test((struct point) {.name = "p6"});




    return 0;
}
