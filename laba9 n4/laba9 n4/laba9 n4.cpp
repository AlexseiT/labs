#include <stdio.h>
#include <time.h>
#include <conio.h>
#include <iostream>
#include <iostream>
#include <stdlib.h>
#include <cstdlib>
using namespace std;
const int N = 3;

int main() {
    int A[N][N], b = 0, a = 0, k = 0;
    srand(1);

m:
    b += 1;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            A[i][j] = rand()% 10 + 1;
            //scanf_s("%d", &A[i][j]);
        }
    }
    a = 0;
    for (int i = 0; i < N; i++) {
        a += A[1][i];
    }
    k = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            k += A[i][j];
        }
        if (a != k) goto m;
        k = 0;
    }
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            k += A[j][i];
        }
        if (a != k) goto m;
        k = 0;
    } 
    for (int i = 0; i < N; i++) {
       for (int j = 0; j < N; j++) {
            printf("%d    ", A[i][j]);
           }
         printf("\n");
         }
    printf("%d\n",b);
}
