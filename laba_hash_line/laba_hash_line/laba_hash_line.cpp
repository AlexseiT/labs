#include <iostream>
#include <cmath>
#include <string.h>

using namespace std;
const int m = 13;
int counter = 0;
int mod(char k)
{
    int rez = (k - 'a') % m;
    return rez;
}

int Hash_line(char T[], char K)
{
    int i;
    i = mod(K);
    while (i < m) {
        if (T[i] == '0') {
            T[i] = K;
            return i;
        }
        if (i + 1 == m) {
            i = 0;
        }
        i++;
        counter++;
    }
}

int main()
{
    int size;
    char s[] = "rabotnmedvluq";
    size = strlen(s);
    char T[m];
    for (int i = 0; i < m; i++) {
        T[i] = '0';
    }
    for (int i = 0; i < size; i++) {
        Hash_line(T, s[i]);
    }
    for (int i = 0; i < m; i++) {
        cout << i << "\t";
    }
    cout << endl;
    for (int i = 0; i < m; i++) {
        cout << T[i] << "\t";
    }
    cout << endl;
    cout << "collision = " << counter;
}
