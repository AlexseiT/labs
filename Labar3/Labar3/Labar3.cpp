#include <iostream>
#include <stdio.h>
#include <conio.h>
#include <time.h>
#include <stdlib.h>

using namespace std;

void FillInc(int A[], int n)
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
        cout << A[i] << " ";
    }
}

void BubbleSort(int A[], int n) {
    int t;
    int C = 0, M = 0;
    for (int i = 1; i <= n - 1 ; i++) 
    {
        for (int j = n; j >= i + 1; j--) 
        {
            C++;
            if (A[j] < A[j - 1])
            {
                M += 3;
                t = A[j];
                A[j] = A[j - 1];
                A[j - 1] = t;
            }
        }
    }
    cout << endl;
    cout << "pract M = " << M << endl;
    cout << "pract C = " << C << endl;
}

int main()
{
    int n;
    int M = 0, C = 0;
    srand(time(NULL));
    for (n = 100; n <= 500; n += 100) {
        int A[n];
        FillRand(A, n);

        /* cout << endl;
         cout << CheckSum(A, n) << endl;
         cout << RunNumber(A, n) << endl;*/

        PrintMas(A, n);

        BubbleSort(A, n);
        cout << endl;
        PrintMas(A, n);
        C = ((n * n) - n) / 2;
        M = 3 * C / 2;
        cout << endl;
        cout << "teor M = " << M << endl;
        cout << "teor C = " << C << endl;

        /*cout << endl;
        cout << CheckSum(A, n) << endl;
        cout << RunNumber(A, n) << endl;*/
    }
}