#include <iostream>
#include <string>

using namespace std;

struct Phone
{
    string Number;
    string F;
    string I;
    string O;
};

void PrintMas(int a[], int n)
{
    for (int i = 0; i < n; i++)
        cout << a[i] << " ";
    cout << endl;
    return;
}

void PrintPhone(Phone *a, int n, int *b) {
    for (int i = 0; i < n; ++i) {
        cout << a[b[i]].F << " ";
        cout << a[b[i]].I << " ";
        cout << a[b[i]].O << " ";
        cout << a[b[i]].Number << " ";
        cout << endl;
    }
        
    cout << endl;
}

int const n = 5;
int main() {
    int b[n];
    int b2[n];
    Phone a[n];

    for (int i = 0; i < n; ++i) {
        b[i] = i;
        b2[i] = i;
    }
    for (int i = 0; i < n; ++i) {
        cin >> a[i].F;
        cin >> a[i].I;
        cin >> a[i].O;
        cin >> a[i].Number;
    }
    cout << endl;

    int t;
    int j;
    for (int i = 1; i < n; i++) {
        t = b[i]; j = i - 1;
        while (j > -1) {
            if (a[t].F >= a[b[j]].F) break;
            b[j + 1] = b[j];
            j--;
        }
        b[j + 1] = t;
    }

    j = 0;

    for (int i = 1; i < n; i++) {
        t = b2[i]; j = i - 1;
        while (j > -1) {
            if (a[t].Number >= a[b2[j]].Number) break;
            b2[j + 1] = b2[j];
            j--;
        }
        b2[j + 1] = t;
    }
    PrintMas(b, n);
    cout << endl;
    PrintPhone(a, n, b);
    PrintMas(b2, n);
    cout << endl;
    PrintPhone(a, n, b2);
}