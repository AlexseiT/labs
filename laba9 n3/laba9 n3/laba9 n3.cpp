#include <stdio.h>
#include <time.h>
#include <conio.h>
#include <iostream>
using namespace std;
const int N = 5;


int main() {
    int A[N][N], k, t=0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            A[i][j] = rand() % 11;
            printf("%d    ", A[i][j]);
        }
        printf("\n");
    }
    printf("_________________________________\n");

    for (int i = 0; i < N; i++) {
        for (int j = t; j < N; j++) {
            k = A[i][j];
            A[i][j] = A[j][i];
            A[j][i] = k;
        }
        t++;
    }
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%d    ", A[i][j]);
        }
        printf("\n");
    }
}