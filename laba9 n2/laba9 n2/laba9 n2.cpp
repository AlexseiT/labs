#include <stdio.h>
#include <time.h>
#include <conio.h>
#include <iostream>
using namespace std;
const int N = 5;


int main() {
    float A[N][N], b = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            A[i][j] = (float)rand() * (9) / RAND_MAX + 1;
            printf("%2.2f  ", A[i][j]);
        }
        printf("\n");
    }
    printf("_________________________________\n");

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            b += A[i][j];
        }
        for (int j = 0; j < N; j++) {
            A[i][j] /= b;
            printf("%2.2f  ", A[i][j]);
        }
        b = 0;
        printf("\n");
    }
}