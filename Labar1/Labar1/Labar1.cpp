#include <iostream>
#include <stdio.h>
#include <conio.h>
#include <time.h>
#include <stdlib.h>
using namespace std;
const int n = 10;

void FillInc (int A[], int n)
{
    for (int i = 0; i < n; i++)
        A[i] = i;
}
void FillDec(int A[], int n)
{
    for (int i = 0; i < n; i++)
        A[i] = n - i;
}
void FillRand(int A[], int n)
{
    for (int i = 0; i < n; i++)
        A[i] = rand() % n;
}
int CheckSum(int A[], int n)
{
    int x = 0;
    for (int i = 0; i < n; i++)
        x += A[i];
    return x;
}
int RunNumber(int A[], int n) {
    int kol = 1;
    for (int i = 1; i < n; i++) {
        if (A[i] < A[i - 1]) kol += 1;
    }
    return kol;
}
void PrintMas(int A[], int n) {
    for (int i = 0; i < n; i++) {
        cout << A[i] << endl;
    }
}



int main()
{
    srand(time(NULL));
    int A[n], x = 0, kol = 1;
    FillRand(A,n);
    PrintMas(A,n);
    cout << endl;
    cout << CheckSum(A, n,) << endl;
    cout << RunNumber(A, n) << endl;
}
