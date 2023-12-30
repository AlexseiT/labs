#include <iostream>
#include <stdio.h>
#include <conio.h>
#include <time.h>
#include <stdlib.h>
using namespace std;
const int n = 10;

void FillRand(int A[], int n)
{
    for (int i = 0; i < n; i++)
        A[i] = rand() % n;
}

void PrintMas(int A[], int n) {
    for (int i = 0; i < n; i++) {
        cout << A[i]<< " ";
    }
    cout << endl;
}

void InsertSort(int a[], int n) {
    int t;
    int j;
    int C;
    int M;
    for (int i = 1; i < n; i++) {
        t = a[i]; j = i - 1;
        C++;
        while (j > -1 && t < a[j]) {
            a[j + 1] = a[j];
            j--;
        }
        a[j + 1] = t;
    }
}

void SelectSort(int A[], int n)
{
    int k;
    int t;
    int C = 0, M = 0;
    for (int i = 0; i < n-1; i++) 
    {
    k = i;
    for (int j = i + 1; j < n;  j++) 
    {
        ++C; 
        if (A[j] < A[k]) k = j;
    }

        if (k != i) {
            M += 3;
            t = A[i];
            A[i] = A[k];
            A[k] = t;
        }
    
    }
    cout << endl;
    cout << "C =" << C << endl;
    cout << "M =" << M << endl;
}

int main()
{
    srand(time(NULL));
    int A[n];
    int M = 0, C = 0;
    FillRand(A, n);
    PrintMas(A, n);
    InsertSort(A, n);
    PrintMas(A, n);
}