/*
Ramon Oliveira de Azevedo
120023419
Ciência da Computação
7° Período
*/

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define NTHREADS 5
#define EXECUTE_START_THREADS 0
#define EXECUTE_MIDDLE_THREADS 1
#define EXECUTE_END_THREADS 2

int execution_control = 0;
int count = 0;
pthread_mutex_t x_mutex;
pthread_cond_t x_cond;

void *createInitialThreads(void *arg){
    char *string = (char*) arg;

    pthread_mutex_lock(&x_mutex);

    while (!(execution_control == EXECUTE_START_THREADS)) {
        pthread_cond_wait(&x_cond, &x_mutex);
    }
    count++;
    if(count == NTHREADS - 3) {
        execution_control = EXECUTE_MIDDLE_THREADS;
        pthread_cond_broadcast(&x_cond);
    }
    printf("%s", string);
    pthread_cond_broadcast(&x_cond);
    pthread_mutex_unlock(&x_mutex);

    string = NULL;
    free(string);
    pthread_exit(NULL);
}

void *createIntermediateThreads(void *arg){

    pthread_mutex_lock(&x_mutex);

    while (!(execution_control == EXECUTE_MIDDLE_THREADS)) {
        pthread_cond_wait(&x_cond, &x_mutex);
    }
    count++;
    execution_control = EXECUTE_END_THREADS;
    pthread_cond_broadcast(&x_cond);
    printf("Sente-se por favor\n");
    pthread_mutex_unlock(&x_mutex);

    pthread_exit(NULL);
}

void *createEndThreads(void *arg){
    char *string = (char*) arg;
    pthread_mutex_lock(&x_mutex);

    while (!(execution_control == EXECUTE_END_THREADS)) {
        pthread_cond_wait(&x_cond, &x_mutex);
    }
    count++;
    printf("%s", string);    

    pthread_mutex_unlock(&x_mutex);

    string = NULL;
    free(string);
    pthread_exit(NULL);
}

int main(int argc, char *argv[]){
    int i;
    pthread_t threads[NTHREADS];

    pthread_mutex_init(&x_mutex, NULL);
    pthread_cond_init(&x_cond, NULL);

    pthread_create(&threads[0], NULL, createInitialThreads, (void*) "Oi Maria!\n");
    pthread_create(&threads[1], NULL, createInitialThreads, (void*) "Oi Jose!\n");
    pthread_create(&threads[2], NULL, createIntermediateThreads, NULL);
    pthread_create(&threads[3], NULL, createEndThreads, (void*) "Ate mais Joao!\n");
    pthread_create(&threads[4], NULL, createEndThreads, (void*) "Ate mais Maria!\n");

    for (i = 0; i < NTHREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    pthread_mutex_destroy(&x_mutex);
    pthread_cond_destroy(&x_cond);
    
    return 0;
}
