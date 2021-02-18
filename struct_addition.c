#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <inttypes.h>

// можно сразу дать новое имя типу стркутуры, сделав анонимную стркутуру с typedef
typedef struct {
    int64_t* array;
    size_t size;
} my_type;


//  СТАТИЧЕСКИЕ ГЛОБАЛЬНЫЕ ПРЕМЕННЫЕ

//  видна лишь внутри файла, сохраняет состояние
static int32_t series_num;

//  генерация последовательности
int32_t series();

//  задание начального значения последовательности
void series_start(int32_t seed);

int32_t series() {
    series_num += 23;
    return series_num;
}

void series_start(int32_t seed) {
    series_num = seed;
}

void perform() {
    //  Вызывая series_start() с некоторым известным целым числом,
    //  мы инициализируем генератор последовательности.
    //После этого вызов series() приводит к генерации следующего
    // элемента последовательности.

    series_start(100);
    for (size_t i = 0; i < 20; ++i) {
        printf("%" PRId32 " ", series());
    }
    printf("\n");

}




//  СТАТИЧЕСКИЕ ЛОКАЛЬНЫЕ ПРЕМЕННЫЕ
//  статическая локальная переменная - это локальная
//  переменная, сохраняющая свое значение между вызовами функций.


//  В реализации ф. генерации последовательности через
//  локальную статическую переменную сразу можно увидеть недостаток
//  Перменная видна лишь в объявленном блоке, а значит начальное значение
//  можно задать лишь при реализации самой функции и никак иначе
//  из другим участков кода переменная не видна
int32_t local_series() {
    //  Статическая клобальная переменная,
    //  при первом вызове значение, присвоенное ей,
    //  или ноль, если переменная объявлена без инициализации
    static int series_num;
    //  каждый раз будет увеличиваться
    series_num+= 23;
    return series_num;
}

void local_perform() {
    for (size_t i = 0; i < 20; ++i) {
        printf("%" PRId32  " ", local_series());
    }
    printf("\n");
}


//  ОБЪЕДИНЕНИЯ
//Если в структурном типе поля идут последовательно (возможно, с пропусками),
// то в объединении все поля начинаются по одному и тому же адресу,
// накладываясь друг на друга. Например:

union qword {
    int64_t integer;
    int32_t parts[2];
};


void union_test() {
    union qword test;
    test.integer = 0xAABBCCDD;
    //Здесь массив из двух чисел типа int32_t
    // накладывается на те же адреса в памяти, что и поле типа int64_t.
    printf("%" PRId32 ", %" PRId32 "\n", test.parts[0], test.parts[1]);
}

//Начиная с C11 структуры и объединения могут быть анонимными
// частями других структур и объединений. Раньше мы писали так:

union vec3d {
    struct {
        double x;
        double y;
        double z;
    } named ;
    double raw[3];
};

//Теперь мы можем не давать имя полю named;
// тогда его поля будут доступны без дополнительной точки:
union new_vec3d {
    struct {
        double x;
        double y;
        double z;
    };
    double raw[3];
};

void test_anonymous_unions() {

    union vec3d v;
    v.named.z = 100;

    union new_vec3d new_v;
    new_v.z = 100;
}


// ПЕРЕЧИСЛЕНИЯ
// Перечисления это численный тип данных на основе int,
// unsigned int, signed int или char.
// Перечисление обозначает некоторый набор констант, снабжённых именами.
// Например, светофор может быть в одном из следующих состояний :

enum light {
    RED = 0,    //можно явно указать int значение переменной
    RED_AND_YELLOW, //  (остальные будут по порядку) 1
    YELLOW, // 2
    GREEN,  // 3
    NOTHING // 4
};

enum http_codes {   // а можно и каждому значение присвоить
    DAB_REQUEST = 400,
    NOT_FOUND = 404,
    FORBIDDEN = 403,
    OK = 200,
    INTERNAL_SERVER_ERROR = 500
};

void print_http_status(enum http_codes code) {
    printf("status code = %d\n", code);
}


//  Реальный пример использования

// результаты операции копирования файла
enum copy_file_result {
    CF_OK,  // = 0
    CF_ERROR_OUT_OF_SPACE,  //  = 1
    CF_ERROR_IO //  = 2
};

const char* cf_error_messages[] = {
        [CF_ERROR_OUT_OF_SPACE] = "Не хватает места",
        [CF_ERROR_IO] = "Ошибка чтеня с диска"
};


enum copy_file_result copy_file(const char* from, const char* to) {

    //... попытка копирования файла

    //  условия возврата ошибок вымышленные, для наглядности

    if (to == NULL) {
        return CF_ERROR_OUT_OF_SPACE;
    }

    if (from == NULL) {
        return CF_ERROR_IO;
    }

    return CF_OK;
}

void perform_copy_file(const char* from, const char* to) {
    enum copy_file_result status = copy_file(from, to);
    printf("%s", cf_error_messages[status]);
}



int main(int argc, char** argv) {
    //  АНОНИМНЫЕ СТРУКТУРЫ
    //  Можно создавать экземпляр структуры не создавая явно её тип;
    //  это будет структура с анонимным типом.

    //Отметим, что структуры и typedef'ы можно объявлять внутри функций и других структур.
    struct {
        const char* name;
        int64_t value;
    } variable;

    my_type a = (my_type) {.array = NULL, .size = 0};

    variable.name = "HELLO";
    variable.value - 44;

    struct {
        const char* name;
        int64_t value;
    } other;

    // Ошибка: два разных анонимных типа никогда не конвертируются друг в друга.
    //other = variable;


    union_test();

    print_http_status(NOT_FOUND);
    print_http_status(403);
    print_http_status(INTERNAL_SERVER_ERROR);


    perform();
    local_perform();

    return 0;
}