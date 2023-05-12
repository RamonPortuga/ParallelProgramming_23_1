/*
Ramon Oliveira de Azevedo
120023419
Ci�ncia da Computa��o
7� Per�odo
*/

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define NTHREADS 5
#define EXECUTE_START_THREADS 0
#define EXECUTE_MIDDLE_THREADS 1
#define EXECUTE_END_THREADS 2

int execution_control = 0;
int x = 0;
pthread_mutex_t x_mutex;
pthread_cond_t x_cond;

void *createInitialThreads(void *arg)
{
    /* Recebe como param uma string qualquer para ser mostrada. */
    char *string = (char*) arg;

    pthread_mutex_lock(&x_mutex);
    /* Executa o trecho apenas quando as threads iniciais forem permitidas. */
    while (!(execution_control == EXECUTE_START_THREADS)) {
        pthread_cond_wait(&x_cond, &x_mutex);
    }
    x++;
    if(x == NTHREADS - 3) {
        execution_control = EXECUTE_MIDDLE_THREADS;
        /* Dispara um aviso para que as threads finais possam ser executadas. */
        pthread_cond_broadcast(&x_cond);
    }
    printf("%s", string);
    /* Dispara um aviso para que as threads intermediarias possam ser executadas. */
    pthread_cond_broadcast(&x_cond);
    pthread_mutex_unlock(&x_mutex);

    string = NULL;
    free(string);
    pthread_exit(NULL);
}

void *createIntermediateThreads(void *arg)
{

    pthread_mutex_lock(&x_mutex);
    /* Executa o trecho apenas quando as threads intermediarias forem permitidas. */
    while (!(execution_control == EXECUTE_MIDDLE_THREADS)) {
        pthread_cond_wait(&x_cond, &x_mutex);
    }
    x++;
    execution_control = EXECUTE_END_THREADS;
    pthread_cond_broadcast(&x_cond);
    printf("Sente-se por favor\n");
    pthread_mutex_unlock(&x_mutex);

    pthread_exit(NULL);
}

void *createEndThreads(void *arg)
{
    /* Recebe como param uma string qualquer para ser mostrada. */
    char *string = (char*) arg;
    pthread_mutex_lock(&x_mutex);
    /* Executa o trecho apenas quando as threads finais forem permitidas. */
    while (!(execution_control == EXECUTE_END_THREADS)) {
        pthread_cond_wait(&x_cond, &x_mutex);
    }
    x++;
    printf("%s", string);    

    pthread_mutex_unlock(&x_mutex);

    string = NULL;
    free(string);
    pthread_exit(NULL);
}

/* Fun��o principal */
int main(int argc, char *argv[])
{
    int i;
    pthread_t threads[NTHREADS];

    /* Inicilaiza o mutex (lock de exclusao mutua) e a variavel de condicao */
    pthread_mutex_init(&x_mutex, NULL);
    pthread_cond_init(&x_cond, NULL);

    /* Cria as threads */
    pthread_create(&threads[0], NULL, createInitialThreads, (void*) "Oi Maria!.\n");
    pthread_create(&threads[1], NULL, createInitialThreads, (void*) "Oi Jos�!.\n");
    pthread_create(&threads[2], NULL, createIntermediateThreads, NULL);
    pthread_create(&threads[3], NULL, createEndThreads, (void*) "At� mais Jo�o!\n");
    pthread_create(&threads[4], NULL, createEndThreads, (void*) "At� mais Maria!\n");

    /* Espera todas as threads completarem */
    for (i = 0; i < NTHREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    /* Desaloca variaveis e termina a execucao */
    pthread_mutex_destroy(&x_mutex);
    pthread_cond_destroy(&x_cond);
}
