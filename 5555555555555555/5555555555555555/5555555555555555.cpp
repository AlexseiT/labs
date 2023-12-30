#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
using namespace std;
int random(int N) { return rand() % N; }
int main() {
    int n = 0;
    cin >> n;
    float* a = new float[n];
    int* b = new int [n];

    for (int i = 0; i < n; i++)
        b[i] = i;
    
    for (int i = 0; i < n; i++)
        a[i] = (float)rand() * 2 * n / RAND_MAX + n;
    

    delete[] a;
    delete[] b;
}