#include <iostream>
#include <math.h>
#include <iomanip>
#include <cmath>
#include <stdlib.h>
#include <stdio.h>

using namespace std;
long int fact(long int n)
{
    if (n == 0) return 1;
    else return n * fact(n - 1);
}

double step(double x, long n) {
    double y = 1;
    int k = 0;
    if (n < 0) {
        n = -n; 
        k++;
    }
    while (n) {
        if (n % 2 == 0) {
            n /= 2;
            x *= x;
        }
        else {
            n--;
            y *= x;
        }
    }
    if (k == 1) return 1 / y;
    else return y;

}

double cosinus(double x) {
    double y = 1;
    double sum = 0;
    int n = 1;
    double eps = 0.0001;
    do {
        y += step(-1, n) * step(x, 2 * n) / fact(2 * n);
        n ++;
    } while (step(x, 2 * n) / fact(2 * n) > eps);

    return y;
}

int main()
{
    double x;
    cin >> x;
    x = x * 3.14 / 180;
    cout << fixed << setprecision(5) << cosinus(x) << endl;
    cout << cos(x) << endl;
}