#include<stdlib.h>
#include<inttypes.h>
#include<stdio.h>
/* Применение в  функциях
 *
 * Напишем функцию подсчета положительных элементов массива
 * эта функция не должна менять сам массив, значит входной параметр
 * будет указатель на неизменемые даннные, разыменование указателя 
 * не позволит менять данные (const слева от *)
*/

size_t count_pos(const int32_t* array, size_t size) {
    size_t count = 0;
    for (size_t i = 0; i< size; i++) {
        if (array[i] > 0) {count++;}
    }
    return count;
}


/* Пример плохой сигнатуры такой же функции: 
 * 1) Через указатель можно изменить данные массива,
 * чего функция не подразумевает.
 *
 * 2) если мы создадим массив как const int32_t arr[], 
 * что эквивалентно const int32_t* - указателю на 0 элемент,
 * то при передаче такого указателя в функцию ниже, возникнет ошибка, 
 * т. к. данный метод не обещает оставить его неизменным!
*/
size_t bad_count_pos(int32_t* array, size_t size);



int main(int argc, char** argv) {
    /* 1
     * Если в начале описания перменной стоит const, значит
     * во время выполнения программы значение переменной
     * не изменяется.
     *
     * Значение должно быть присвоино сразу при
     * инициализации перменной.
    */
    const int16_t a = 28000;
    printf("Значение а: %" PRId16, a);
    /* a = 34  - compile error */    

    /* Константу можно изменить через указатель, компиляция пройдет, но
     * с предупреждением warning
    */
    int16_t* pi = &a;
    *pi = 12;
    printf("Значение а: %" PRId16, a);



    /* CONST ПРИ РАБОТЕ С УКАЗАТЕЛЯМИ! 
     *
     * ПРАВИЛО:
     *
     * const слева от звездочки защищает то, на что мы указываем 
     * (значит изменить данные через разыменование указателя не удастся,
     * но изменить перенаправить указатель на другую ячейку памяти сможем);
    */
    int16_t b = 14000;
    int16_t const* const_data = &b;
    
    const int16_t* const_data2 = &b;    /* То же самое, что и выше, главное, что const слева от * !! */

    /* *const_data = 24;    error  */

    int16_t other = 0;
    const_data = &other;    /* ok  */



    /* 
     * const справа от звездочки - защищает сам указатель от изменения
     * (значит изменить данные через разыменование указателя можно,
     * но перенаправлять указатель на другую ячейку памяти - нет).
    */

    int16_t c = 7000;
    int16_t* const const_pointer = &c;

    *const_pointer = 3500;  /* ok  */

    /* const_pointer = &other;  error  */
    
    /*
     * А значит, совместив оба правила мы получим:
     *
     * незименяемый указатель, перенаправить который на другую ячейку памяти
     * нельзя;
     *
     * указывающий на неизменяемые данные, значит через разыменование
     * указателя не удастся изменить эти самые данные.
    */


    int16_t d = 11111;
    const int16_t* const const_pointer_data = &d;

    /* *const_pointer_data = 12122;    error */
    /* const_pointer_data = &other;    error */



    /* При всем этом наша перменная не обязательно
     * должна быть определена как const, тк эти правила ограничивают
     * лишь РАБОТУ С УКАЗАТЕЛЕМ
     *
     * работая напрямую через переменные, я их изменил, несмотря на ограничения на указатели :Ь
    */

    d = 4096;
    c = 2048;
    b = 1024;


    return 0;
}




