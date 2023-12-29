#include <iostream>
#include <ctime>

void SelectSort(float a[], int n)
{
    int k;
    float add;
    for (int i = 0; i < n - 1; i++)
    {
        k = i;
        for (int j = i + 1; j < n; j++)
        {
            if (a[j] < a[k]) k = j;
        }
        if (k != i) {
            add = a[i];
            a[i] = a[k];
            a[k] = add;
        }
    }
}

void InsertSort(float a[], int n)
{
    int j;
    float t;
    for (int i = 1; i < n; i++) {
        t = a[i];
        j = i - 1;

        while ((j > -1) && (t < a[j])) {
            a[j + 1] = a[j];
            j = j - 1;
        }
        a[j + 1] = t;
    }
}

void QuickSort(float a[], int L, int R)
{
    float k;
    int i = L, j = R;
    int x = a[L];

    while (i <= j) {
        while (a[i] < x)  i++;
        while (a[j] > x)  j--;
        if (i <= j) {
            k = a[i];
            a[i] = a[j];
            a[j] = k;
            i++;
            j--;
        }
    }
    if (L < j) QuickSort(a, L, j);
    if (i < R) QuickSort(a, i, R);
}