#include <iostream>
using namespace std;

void Fillnc(int A[], int n) {
    for (int i = 0; i < n; ++i)
        A[i] = i;
}
void FillDec(int A[], int n) {
    for (int i = 0; i < n; ++i) {
        A[i] = n - i;
    }
}
void FillRand(int A[], int n) {
    for (int i = 0; i < n; ++i)
        A[i] = rand() % 20;
}
void PrintMas(int A[], int n) {
    for (int i = 0; i < n; ++i)
        cout << A[i] << " ";
    cout << endl;
}

int M = 0, C = 0;
void QuickSort(int* A, int n) {
    for (int i = n / 2 - 1; i >= 0; --i){

    }
}


int main() {
    const int n = 10;
    int A[n];
    FillRand(A, n);
    PrintMas(A, n);
    QuickSort(A, n);
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
        QuickSort(A, n);

        FillDec(A, k);
        QuickSort(A, n);

        FillRand(A, k);
        QuickSort(A, n);
        cout << "\n";
        delete[] A;
    }

}