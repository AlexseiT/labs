/*Функция возведения в степень за log(n)*/
#include <iostream>
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
int main()
{
    std::cout << "Hello World!\n";
}

