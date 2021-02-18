#include<stdio.h>
#include<stdlib.h>
#include<inttypes.h>
int main(int argc, char* argv[])
{
    int32_t N;
    printf("Enter size of array to create:");
    scanf("%" SCNd32, &N);
    
    char* A = (char*) malloc(N); //malloc() return void*
    if (A == NULL) { //malloc return NULL if didn't gave memory
        printf("Os didn't gave memory. Exit...\n");
        return 1;
    }


    for (int i = 0; i < N; i++) {
        A[i] = i;
    }
    
    printf("Array successfully created!\n");
    system("pause");

    return 0;

}
