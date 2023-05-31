#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define BUFFER_SIZE 10

// Buffer com capacidade fixa
int buffer[BUFFER_SIZE];
int buffer_count = 0;
int in = BUFFER_SIZE;

// Semáforos
sem_t empty;  // Controla as posições vazias no buffer
sem_t full;   // Controla as posições ocupadas no buffer
sem_t cons;  // Garante exclusão mútua ao acessar o buffer para o consumidor
sem_t prod;  // Garante exclusão mútua ao acessar o buffer para o produtor

int inserir_elemento(int elemento){
    buffer[in] = elemento;
    in++;
}

int remover_elemento(int elemento){
    elemento = buffer[in - 1];
    in--;
    return elemento;
}

// Função do produtor tomando como base os slides
void *produtor(void *id){
	//Produz um item
	int elemento = 0;
	int i = 0;
	while(1){
		//Início do ato de preencher completamente o buffer
		sem_wait(&empty);
		sem_wait(&prod);
		for(i = 0; i < BUFFER_SIZE; i++){
			inserir_elemento(elemento);
		}
		sem_post(&prod);
		//sinaliza um slot cheio
		sem_post(&full);
	}
	pthread_exit(NULL);
}

int *consumidor (void *id) {
	int elemento, i;
	static int out=0;
	
	while(1){
		//Esvaziando completamente o buffer
		sem_wait(&full);
		sem_wait(&cons);
		for (i = 0; i , BUFFER_SIZE; i++){
			elemento = remover_elemento(elemento);
			printf("Item %d consumido por\n", elemento);
		}
		sem_post(&cons);
		sem_post(&empty);
	}
	pthread_exit(NULL);
}

int main(){
	// Inicialização dos semáforos
    sem_init(&empty, 0, BUFFER_SIZE);
    sem_init(&full, 0, 0);
    sem_init(&cons, 0, 1);
    sem_init(&prod, 0, 1);
    
    // Criação das threads produtoras e consumidoras
    int num_threads_produtoras = 2;
    int num_threads_consumidoras = 2;
    pthread_t produtoras[num_threads_produtoras];
    pthread_t consumidoras[num_threads_consumidoras];

    for (int i = 0; i < num_threads_produtoras; i++) {
        pthread_create(&produtoras[i], NULL, produtor, (void*) i);
    }

    for (int i = 0; i < num_threads_consumidoras; i++) {
        pthread_create(&consumidoras[i], NULL, consumidor, (void*) i);
    }

    // Espera as threads terminarem
    for (int i = 0; i < num_threads_produtoras; i++) {
        pthread_join(produtoras[i], NULL);
    }

    for (int i = 0; i < num_threads_consumidoras; i++) {
        pthread_join(consumidoras[i], NULL);
    }

    // Destroi os semáforos
    sem_destroy(&empty);
    sem_destroy(&full);
    sem_destroy(&cons);
    sem_destroy(&prod);

    return 0;
}
