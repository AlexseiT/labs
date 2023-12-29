#include <iostream>
#include <ctime>
using namespace std;

void Fillnc(int A[], int n) {
    for (int i = 0; i < n; ++i)
        A[i] = i;
}
void FillDec(int A[], int n) {
    for (int i = 0; i < n; ++i) 
        A[i] = n - i;
    
}
void FillRand(int A[], int n) {
    srand(time(NULL));
    for (int i = 0; i < n; ++i)
        A[i] = rand() % 20;
}
void PrintMas(int A[], int n) {
    for (int i = 0; i < n; ++i)
        cout << A[i] << " ";
    cout << endl;
}

int M = 0, C = 0;
void BuildHeap(int* A, int n, int i) {
    int largest = i;

    int l = 2 * i + 1, r = 2 * i + 2;

    C++;
    if (l < n && A[l] > A[largest])
        largest = l;
    C++;
    if (r < n && A[r] > A[largest])
        largest = r;
    C++;
    if (largest != i) {
        M += 3;
        swap(A[i], A[largest]);
        BuildHeap(A, n, largest);
    }

}
void HeapSort(int* A, int n) {
    for (int i = n / 2 - 1; i >= 0; --i)
        BuildHeap(A, n, i);

    for (int i = n - 1; i >= 0; --i) {
        M += 3;
        swap(A[0], A[i]);
        BuildHeap(A, i, 0);
    }
}

void Sort(int* A, int n) {
    HeapSort(A, n);
    cout << "\t" << C + M << "\t";
    M = 0; C = 0;
}

int main() {
    const int n = 10;
    int A[n];
    FillRand(A, n);
    PrintMas(A, n);

    HeapSort(A, n);
    PrintMas(A, n);
    M = 0; C = 0;

    cout << "  n   \t\t\tHeapSort(M+C)\t\t \n"
        << "      \tinc\t \tdec\t \trand\t \n";
    int k;
    for (int i = 1; i < 6; ++i) {
        cout << " " << i * 100 << " ";
        k = i * 100;
        int* A = new int[k];
        Fillnc(A, k);
        Sort(A, k);

        FillDec(A, k);
        Sort(A, k);

        FillRand(A, k);
        Sort(A, k);
        cout << "\n";
        delete[] A;
    }

}