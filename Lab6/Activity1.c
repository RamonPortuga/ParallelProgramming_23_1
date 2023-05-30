//variaveis do problema
int Buffer[N]; //espaco de dados compartilhados (N = tamanho do buffer)
int count=0, out=0; //variaveis de estado
//variaveis para sincronizacao
pthread_mutex_t mutex;
pthread_cond_t cond_cons, cond_prod;
//preenche todos os espac ¸os do Buffer ou bloqueia a thread caso o Buffer n ~ao esteja vazio
void Insere (int item[]) {
	pthread_mutex_lock(&mutex);
	while(count > 0) { //espera ter todos os espacos vazios no buffer
		pthread_cond_wait(&cond_prod, &mutex);
	}
	for(int i=0; i<N; i++) //copia vetor de entrada para o buffer
		Buffer[i] = itens[i];
	count = N; //indica que o buffer est ´a cheio
	//sinaliza para os consumidores
	pthread_mutex_broadcast(&cond_cons);
	pthread_mutex_unlock(&mutex);
}
//retira um item do Buffer ou bloqueia a thread caso o Buffer esteja vazio
int *Retira (void) {
	int item; //copia do item que sera retirado
	pthread_mutex_lock(&mutex);
	while(count == 0) { //espera ter algum item no buffer
		pthread_cond_wait(&cond_cons, &mutex);
	}
	item = Buffer[out];
	out = (out + 1) % N;
	count--; //indica que o buffer tem um item a menos
	//sinaliza um produtor apenas quando o buffer estiver vazio
	if(count==0) pthread_cond_signal(&cond_prod);
		pthread_mutex_unlock(&mutex);
	return item;
}
