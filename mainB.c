#include<stdio.h>
#include<pthread.h>

// QUESTÃO 3- b)

#define N 5

int linha, j;
int X[N][N];
pthread_t threads[N];
pthread_barrier_t bar1, bar2;

void f(linha) {
    for (j = 0; j < N; j++) {
        if (j == 0) {
            X[linha][j] = rand();
            printf("Primeira coluna: %d \n", X[linha][j]);
        }
        else {
            X[linha][j] = X[rand() % N][rand() % j];
            printf("Coluna(s) restante(s): %d \n", X[linha][j]);
        }
        pthread_barrier_wait(bar1);
    }
    
    pthread_barrier_wait(bar2);
}

int main(void){
    pthread_barrier_init(&bar1, NULL, N);
    pthread_barrier_init(&bar2, NULL, N+1);

    for (linha = 0; linha < N; linha++) {
        threads[linha] = pthread_create(&threads[linha], NULL, f, linha);
    }

    pthread_barrier_wait(bar2);
}
