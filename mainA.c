#include<stdio.h>
#include<time.h>

// QUESTÃO 3- a)

#define N 20

int main(void){
    int j, i;
    int X[N][N];

    double time_spent = 0.0;
    clock_t begin = clock();
  
    for (j = 0; j < N; j++) {
        for (i = 0; i < N; i++) {
            if (j == 0) {
                X[i][j] = rand();
            }
            else {
                X[i][j] = X[rand() % N][rand() % j];
            }
        }
    }

  for (int j = 0; j < N; j++) {
    for (int i = 0; i < N; i++) {
      printf("Elemento X[%d][%d]: %d \n", i, j, X[i][j]);
    }
  }
  
  clock_t end = clock();
  time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
  printf("Tempo de execucao: %f", time_spent);
}