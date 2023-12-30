#include <stdio.h>
#include <time.h>
#include <conio.h>
#include <iostream>
using namespace std;
const int M = 10; 
const int N = 20; 


int main() {
    int i, j, A[M][N], k;
    for (i = 0; i < M; i++) {
        for (j = 0; j < N; j++) {
            A[i][j] = rand() % 10 + 1;
            printf("%d  ", A[i][j]);
        }
        printf("\n");
    }
    printf("____________________\n");

    for (i = 1; i < M;) {
        for (j = 0; j < N; j++) {
            k = A[i][j];
            A[i][j] = A[i - 1][j];
            A[i - 1][j] = k;
        }
        i += 2;
    }
    for (i = 0; i < M; i++) {
        for (j = 0; j < N; j++) {
            printf("%d  ", A[i][j]);
        }
        printf("\n");
    }
}