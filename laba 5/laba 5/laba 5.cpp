#include <stdlib.h>
#include <stdio.h>
#include <locale.h>
#include <conio.h>
#include <math.h>


int main() {
   setlocale(LC_ALL, "Russian");
   float  pi = 4, x, b = 1;
   int i = 1, N;
   printf("Введите N\n");
   scanf_s("%d", &N);

   do {
	i++;
	x = pow(2 * i - 1, -1) * pow(-1, i - 1);
	b += x;
	} while (i <= N);

	pi *= b;
	printf("pi = %7.5f\n",pi);
}