#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
using namespace std;
int main() {
    int n = 0;
    cin >> n;
    int *A = new int[n + 1];
    for (int i = 0; i < n + 1; i++)
        A[i] = i;
    for (int i = 2; i < n + 1; i++)
    {
        if (A[i] != 0)
        {
            cout << A[i] << endl;
            for (int j = i * i; j < n + 1; j += i)
                A[j] = 0;
        }
    }
    cin.get();
    delete[] A;
}