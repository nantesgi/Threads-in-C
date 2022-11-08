#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// QUESTÃO 3- c)

#define N 20

int X[N][N];
sem_t sem[N][N];
pthread_barrier_t fim;

struct params {
  int i;
  int j;
};

void *f(void *param) {
  struct params *p = (struct params*)param;
  int i = (*p).i;
  int j = (*p).j;

  if (j == 0) {
    X[i][j] = rand();
  }
  else {
    int linha = rand() % N;
    int coluna = rand() % j;
    sem_wait(&sem[linha][coluna]);
    X[i][j] = X[linha][coluna];
  }

  for(int k = 0; k < N * N; k++) {
      sem_post(&sem[i][j]);  
  }

  if (j == N - 1)
    pthread_barrier_wait(&fim);

  return 0;
}

int main() {
  pthread_t threads[N][N];
  struct params elem[N * N];

  pthread_barrier_init(&fim, NULL, N + 1);

  double time_spent = 0.0;
  clock_t begin = clock();
  
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      sem_init(&sem[i][j], 0, 0);  
    }
  }

  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      elem[N * i + j].i = i;
      elem[N * i + j].j = j;
      pthread_create(&threads[i][j], NULL, f, &elem[N * i + j]);
    }
  }

  pthread_barrier_wait(&fim);

  for (int j = 0; j < N; j++) {
    for (int i = 0; i < N; i++) {
      printf("Elemento X[%d][%d]: %d \n", i, j, X[i][j]);
    }
  }

  clock_t end = clock();
  time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
  printf("Tempo de execucao: %f", time_spent);
}