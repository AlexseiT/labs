#include <iostream>
#include <stdlib.h>
#include <stdio.h>

#include <vector>

using namespace std;

int main() {
    int n = 0;
    cout << n << endl;
    int* A = new int[n + 1];
    for (int i = 0; i < n + 1; i++)
        A[i] = i;
    for (int p = 2; p < n + 1; p++)
    {
        if (A[p] != 0)
        {
            cout << A[p] << endl;
            for (int j = p * p; j < n + 1; j += p)
                A[j] = 0;
        }
    }
    cin.get();
}
