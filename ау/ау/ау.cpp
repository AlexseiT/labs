#include <stdlib.h>
#include <stdio.h>
#include <locale.h>
#include <conio.h>
#include <math.h>


int main() {
	setlocale(LC_ALL, "Russian");
	float a;
	int i = 0;
	scanf_s("%f ", &a);

	while (i < 100) {
		if (a < 1) { a = a * 2; printf("0\n"); }
		printf("a = %f\n", a);
		if (a >= 1) { a = a - 1; printf("1\n"); }
		printf("a = %f\n", a);
		i++;
	}
}
