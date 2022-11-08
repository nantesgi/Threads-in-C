#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>

// QUESTÃO 3- b)

#define N 15

int linha, j, k;
int X[N][N];
sem_t sem[N][N];
pthread_t threads[N];
pthread_barrier_t fim;

void *f(void *l, void *j) {
    int coluna = *((int*)j);
    int linha = *((int*)l);
    
    if (coluna == 0) {
        X[linha][coluna] = rand();
    }
    else {
        int linha = rand() % N;
        int coluna = rand() % coluna;
        int j = *((int*)coluna);
        int l = *((int*)linha);

        sem_wait(sem[linha][coluna]);
        X[l][j] = X[linha][coluna];
    }

    for (k = 0; k < N; k++) {
        int j = *((int*)coluna);
        int l = *((int*)linha);
        sem_post(&X[l][j]);
    }
    
    if (coluna == N-1) {
        pthread_barrier_wait(fim);
    }
}

int main(int argc, char *argv[]){
    pthread_barrier_init(&fim, NULL, N+1);

    for (linha = 0; linha < N; linha++) {
        for (j = 0; j < N; j++) {
            sem[linha][j] = sem_init(*sem, 0, 1);
        }
    }

    for (linha = 0; linha < N; linha++) {
        for (j = 0; j < N; j++) {
            int l = linha;
            sem[linha][j] = pthread_create(&threads[linha], NULL, f, (void*)&l);
        }
    }

    pthread_barrier_wait(fim);

    for (j = 0; j < N-1; j++) {
            for (linha = 0; linha < N; linha++) {
                if (j == 0) {
                    X[linha][j] = rand();
                    printf("Elemento X[%d][%d]: %d \n", linha, j, X[linha][j]);
                }
                else {
                    X[linha][j] = X[rand() % N][rand() % j];
                    printf("Elemento X[%d][%d]: %d \n",linha, j, X[linha][j]);
                }
            }
        }
    
}