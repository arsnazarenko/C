#include <stdio.h>
#include <stdlib.h>

void foo(int* p) 
{
    printf("Got: *p = %d\n", *p);
    *p += 10;
    printf("Did: *p = %d\n", *p);
}


int main(int argc, char* argv[])
{
    int x = 7;
    printf("x = %d\n", x);
    foo(&x);
    printf("x = %d\n", x);
    return 0;
}

