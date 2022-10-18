#include<stdio.h>

// QUESTÃO 3- a)

#define N 5

int main(void){
    int j, i;
    int X[N][N];

    for (j = 0; j < N; j++) {
        for (i = 0; i < N; i++) {
            if (j == 0) {
                X[i][j] = rand();
                printf("Primeira coluna: %d \n", X[i][j]);
            }
            else {
                X[i][j] = X[rand() % N][rand() % j];
                printf("Coluna(s) restante(s): %d \n", X[i][j]);
            }
        }
    }
}