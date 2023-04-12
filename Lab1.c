/*
Ramon Oliveira de Azevedo
120023419
Ciência da Computação - UFRJ
7° Período
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREADS 2
#define SIZE 10000

int vector[SIZE];

void create_vector(){
    printf("Creating vector with %d positions:\n", SIZE);
    for (int i = 0; i < SIZE; i++) {
        vector[i] = 1;
    }
    printf("\nSuccessfully created vector!\n\n");
}

void* multiply_by_2(void* id_threads) {
    int id = *((int*) id_threads);

    for (int i = id; i < SIZE; i = i + 2) {
        vector[i] *= 2;
    }

    pthread_exit(NULL);
}

void print_vector(){
    printf("\nPrinting Vector...\n");
    for (int i = 0; i < SIZE; i++) {
        printf("Index:\t%d\tValue:\t%d\n", i, vector[i]);
    }
}

void test(){
    printf("\nTesting...\n");
    int sucess = 1;
    for (int i = 0; i < SIZE; i++) {
        vector[i] /= 2;
        if(vector[i] != 1){
            sucess = 0;
            printf("\nTest Failed!\n\n");
        }
    }
    if(sucess){
        printf("\nSuccess! The vectors are the same! The threads worked!\n\n");
    }
}

int main() {
    printf("Starting...\n\n");
    pthread_t threads[NUM_THREADS];
    int id_threads[NUM_THREADS];

    create_vector();

    printf("\nStarting the process of creating and executing the threads.\n");

    for (int i = 0; i < NUM_THREADS; i++) {
        id_threads[i] = i;
        pthread_create(&threads[i], NULL, multiply_by_2, (void*) &id_threads[i]);
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    test();

    print_vector();
    
    printf("\n\n");

    printf("The end\n\n");

    return 0;
}
