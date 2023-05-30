#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define BUFFER_SIZE 3
#define NTHREADS 4

// Buffer com capacidade fixa
int Buffer[BUFFER_SIZE];
int count = 0;
int out = 0;

// Semáforos
sem_t empty;  // Controla as posições vazias no buffer
sem_t full;   // Controla as posições ocupadas no buffer
sem_t mutexProd;  // Garante exclusão mútua ao acessar o buffer
sem_t mutexCons;

void Insere (int itens[]) {
	while(count > 0) { 
		sem_wait(&empty);
	}
	sem_wait(&mutexProd);
	for(int i=0; i < BUFFER_SIZE; i++) 
		Buffer[i] = itens[i];
	count = BUFFER_SIZE;
	printf("Quantidade do Buffer:\t%d", count);
	sem_post(&mutexProd);
	
	sem_post(&full);
}

int *Retira (void) {
	int item;
	while(count == 0) { 
		sem_wait(&full);
	}
	sem_wait(&mutexCons);
	item = Buffer[out];
	out = (out + 1) % BUFFER_SIZE;
	count--;
	printf("Quantidade do Buffer:\t%d", count);
	sem_post(&mutexCons);
	
	if(count==0)
		sem_wait(&empty);
	return item;
}

int main(){
    int i;
    int vetor[BUFFER_SIZE];
    pthread_t threads[NTHREADS];
    
    // Inicialização dos semáforos
    sem_init(&empty, 0, BUFFER_SIZE);
    sem_init(&full, 0, 0);
    sem_init(&mutexProd, 0, 1);
    sem_init(&mutexCons, 0, 1);

    // Criação das threads produtoras e consumidoras
    pthread_t produtor, consumidor;
    int id1 = 1, id2 = 2;

	for (i = 0; i < BUFFER_SIZE; i++){
		vetor[i] = i;
	}

    pthread_create(&produtor, NULL, Insere, vetor);
    pthread_create(&consumidor, NULL, Retira, NULL);
    
     /* Espera todas as threads completarem */
    for (i = 0; i < NTHREADS; i++)
    {
        pthread_join(threads[i], NULL);
    }
}
