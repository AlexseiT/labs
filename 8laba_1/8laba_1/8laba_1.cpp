#include <iostream>
#include <string>

using namespace std;

struct Struct
{
    unsigned short number;
    unsigned short count1;
    unsigned short count2;
};

void PrintMas(int a[], int n)
{
    for (int i = 0; i < n; i++)
        cout << a[i] << " ";
    cout << endl;
    return;
}

void PrintStruct(Struct* a, int n, int* b) {
    for (int i = 0; i < n; ++i) {
        cout << a[b[i]].number << " ";
        cout << a[b[i]].count1 << " ";
        cout << (a[b[i]].count2 * 100) / a[b[i]].count1 << "% ";
        cout << endl;
    }

    cout << endl;
}

void StructEnter(Struct* a, int n) {
    for (int i = 0; i < n; ++i) {
        cin >> a[i].number;
        cin >> a[i].count1;
        cin >> a[i].count2;
    }
    cout << endl;
}

void Sort(Struct* a, int* b, int n) {
    int t;
    int j;
    for (int i = 1; i < n; i++) {
        t = b[i]; j = i - 1;
        while (j > -1) {
            if (a[t].count2 >= a[b[j]].count2) break;
            b[j + 1] = b[j];
            j--;
        }
        b[j + 1] = t;
    }
}

int main() {
    int n;

    cin >> n;

    int* b = new int[n];

    Struct* a = new Struct[n];

    for (int i = 0; i < n; ++i) {
        b[i] = i;
    }

    StructEnter(a, n);

    Sort(a, b, n);

    PrintMas(b, n);

    cout << endl;

    PrintStruct(a, n, b);
    
}