#include <stdlib.h>
#include <stdio.h>
#include <locale.h>
#include <conio.h>
#include <math.h>


int main() {
	setlocale(LC_ALL, "Russian");
	int n, a, i, j = 2, k = 0, kk = 0;
	printf("Введи n\n");
	scanf_s("%d", &n);
	i = n;
	do {

		do {

			if (i % j == 0) k += 1;
			j += 1;
		} while (j <= i);
		if (k == 1) { printf("%d ", i); kk += 1; }
		i -= 1;
		k = 0;
		j = 2;

	} while (i >= 2);

	printf(" kol = %d", kk);
}