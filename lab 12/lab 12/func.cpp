#include <iostream>
#include <ctime>

void SelectSort(double* a, int n)
{
    int k;
    double t;
    for (int i = 0; i < n - 1; i++)
    {
        k = i;
        for (int j = i + 1; j < n; j++)
        {
            if (a[j] < a[k]) k = j;
        }
        if (k != i) {
            t = a[i];
            a[i] = a[k];
            a[k] = t;
        }
    }
}
void InsertSort(double* a, int n) {
    double t;
    int j;
    for (int i = 1; i < n; i++) {
        t = a[i]; j = i - 1;
        while (j > -1 && t < a[j]) {
            a[j + 1] = a[j];
            j--;
        }
        a[j + 1] = t;
    }
}

void BuildHeap(double* a, int n, int i) {
    int largest = i;
    double t;
    int l = 2 * i + 1, r = 2 * i + 2;


    if (l < n && a[l] > a[largest])
        largest = l;
 
    if (r < n && a[r] > a[largest])
        largest = r;

    if (largest != i) {
        t = a[i];
        a[i] = a[largest];
        a[largest] = t;
        BuildHeap(a, n, largest);
    }

}
void HeapSort(double* a, int n) {
    double t;
    for (int i = n / 2 - 1; i >= 0; --i)
        BuildHeap(a, n, i);

    for (int i = n - 1; i >= 0; --i) {
        t = a[0];
        a[0] = a[i];
        a[i] = t;
        BuildHeap(a, i, 0);
    }
}

void QuickSort(double* a, int L, int R)
{
    double k;
    int i = L, j = R;
    double x = a[L];
    while (i <= j)
    {
        while (a[i] < x) {
            i++;
        }
        while (a[j] > x) {
            j--;
        }
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