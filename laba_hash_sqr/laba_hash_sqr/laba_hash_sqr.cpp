#include <iostream>
#include <cmath>
#include <string.h>

using namespace std;
const int m = 13;
int counter = 0;

int mod(char k)
{
    int result = (k - 'a') % m;
    return result;
}

void Hash_square(char T[], char K)
{
    int h = mod(K);
    int d = 1;
    while (true) {
        if (T[h] == '0') {
            T[h] = K;
            break;
        }
        counter++;
        if (d >= m) {
            cout << "Table overflow!";
            break;
        }
        h = h + d;
        if (h >= m) {
            h = h - m;
        }
        d = d + 2;
    }
}


int main()
{
    int size;
    char s[] = "rabotnmedvluq";
    size = strlen(s);
    char T[m];
    for (int i = 0; i < m; i++) {
        cout << i << "\t";
        T[i] = '0';
    }
    for (int i = 0; i < size; i++) {
        Hash_square(T, s[i]);
    }
    cout << endl;
    for (int i = 0; i < m; i++) {
        cout << T[i] << "\t";
    }
    cout << endl;
    cout << "collision = " << counter;
}
