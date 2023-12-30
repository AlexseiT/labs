#include <stdlib.h>
#include <stdio.h>
#include <locale.h>
#include <conio.h>
#include <math.h>

long int fact(long int m)
{
    if (m == 0 || m == 1) return 1;
    return m * fact( m - 1);
}

int main()
{
    setlocale(LC_ALL, "Russian");

    float S = 1, x, N;

    int i, j;

    printf("Введите N и x ");    
    scanf_s("%f %f", &N, &x);

    for (int i = 1; i <= N; i++) {
        S += pow(x, i) / fact(i);
    }
 

    printf("S = %6.2f ", S);
    system("PAUSE");
    return 0;
}
