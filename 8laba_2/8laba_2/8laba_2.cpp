#include <iostream>
#include <string>

using namespace std;

struct Struct
{
    unsigned short number;
    unsigned short area;
    string F;
    unsigned short count;
};

void Print(string a[], int n, int kol, int kol1)
{
    for (int i = 0; i < n; i++)
        cout << a[i] << " ";
    cout << endl;
    cout << endl;
    cout << "Rooms = " << n << endl;
    cout << "Students = " << kol << endl;
    cout << "Average area = " << kol1 / kol << endl;
}
void PrintStruct(Struct* a, int n) {
    for (int i = 0; i < n; ++i) {
        cout << a[i].number << " ";
        cout << a[i].area << " ";
        cout << a[i].F << " ";
        cout << a[i].count << " ";
        cout << endl;
    }

    cout << endl;
}
void Sort(Struct* a, int n) {
    Struct t;
    int j;
    for (int i = 1; i < n; i++) {
        t = a[i]; j = i - 1;
        while (j > -1) {
            if (t.F >= a[j].F) break;
            a[j + 1] = a[j];
            j--;
        }
        a[j + 1] = t;
    }
}
void StructEnter(Struct* a, int n, int &kol, int &kol1) {
    for (int i = 0; i < n; ++i) {
        cin >> a[i].number;
        cin >> a[i].area;
        cin >> a[i].F;
        cin >> a[i].count;
        kol += a[i].count;
        kol1 += a[i].area;
    }
    cout << endl;
}
void Completion(string* b, Struct* a, int n)
 {
    int j = 0;
    for (int i = 0; i < n - 1; ++i) {
        if (a[i].F != a[i + 1].F) {
            b[j] = a[i].F;
            j++;
        }
    }
    b[j] = a[n - 1].F;

}

int main() {

    int n, kol = 0, kol1 = 0, n1 = 1;

    cin >> n;

    Struct* a = new Struct[n];

    StructEnter(a, n, kol, kol1);

    Sort(a, n);

    for (int i = 0; i < n-1; ++i) {

        if(a[i].F != a[i + 1].F) n1 += 1;
    }

    string* b = new string[n1];

    cout << "Faculties = " << n1 << endl;

    cout << endl;

    Completion(b, a, n);

    Print(b, n1, kol, kol1);

}