#include <iostream>

using namespace std;
int const n = 10;

void FillInc(int a[], int n) //заполнение массива возрастающими числами
{
    for (int i = 0; i < n; i++)
        a[i] = i + 1;
    return;
}

void PrintMas(int a[], int n) //вывод на экран элементов массива
{
    for (int i = 0; i < n; i++)
        cout << a[i] << " ";
    cout << endl;
    return;
}

void Heapify(int a[], int L, int n)
{
    int R = n;
    int x = a[L];
    int i = L;

    do {
        int j = 2 * i;
        if (j > R) break;
        if (j < R && a[j + 1] <= a[j])
            j++;
        if (x <= a[j]) break;
        a[i] = a[j];
        i = j;
    } while (true);

    a[i] = x;
}

void Heapsort(int a[], int n)
{
    int L = n / 2;
    while (L > 0) {
        Heapify(a, L, n);
        L--;
    }

    int R = n, t;
    while (R > 1) {
        t = a[1];
        a[1] = a[R];
        a[R] = t;
        R--;
        Heapify(a, 1, R);
    }
}

int main()
{
    int a[n];
    FillInc(a, n);
    PrintMas(a, n);
    Heapsort(a, n);
    PrintMas(a, n);
}
