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

void* multiply_by_2(void* id_threads) {
    int id = *((int*) id_threads);

    for (int i = id; i < SIZE; i = i + 2) {
        //printf("Changing index %d\n", i);
        vector[i] *= 2;
    }

    pthread_exit(NULL);
}

int main() {
    printf("Starting...\n\n");
    pthread_t threads[NUM_THREADS];
    int id_threads[NUM_THREADS];

    for (int i = 0; i < SIZE; i++) {
        vector[i] = i;
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        id_threads[i] = i;
        pthread_create(&threads[i], NULL, multiply_by_2, (void*) &id_threads[i]);
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    for (int i = 0; i < SIZE; i++) {
        printf("Index:\t%d\tValue:\t%d\n", i, vector[i]);
    }
    printf("\n\n");

    printf("The end\n\n");

    pthread_exit(NULL);

    return 0;
}

