#include<stdio.h>
#include<inttypes.h>
#include<stdlib.h>


int main(int argc, char* argv[]) {
    
    int32_t N;
    printf("Enter size of array to create:");
    scanf("%" SCNd32, &N);

    /*
        sizeof() выполняется в момент компиляции
        работает и с типом и с переменной и с числовым литералом
    */ 
    
    for (int k = 0; k < 1000; k++) {
        int32_t* A = (int32_t*) malloc(N * sizeof(int32_t));
        if (A == NULL) { //malloc return NULL if didn't gave memory
            printf("Os didn't gave memory. Exit...\n");
            return 1;
        }


        for (int i = 0; i < N; i++) {
            A[i] = i;
        }

        free(A);
    }
   
    
    printf("Array successfully created!\n");
    system("pause");
    return 0;


}
