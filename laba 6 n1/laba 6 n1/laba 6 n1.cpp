#include <stdlib.h>
#include <stdio.h>
#include <locale.h>
#include <conio.h>
#include <math.h>

int random(int N) { return rand() % N; }
const int n = 20;

int main() {

	setlocale(LC_ALL, "Russian");

	int   i, pl, mn, a[n], b = 10;
	for (int i = 0; i < n; i++) {
		a[i] = random(b + b + 1) - b ;
	}

	printf("Положительные числа\n");
	for (int i = 0; i < n; i++) {
		if (a[i] > 0) printf("%d  ",a[i]);
	}

	printf("\nОтрицательные числа\n");
	for (int i = 0; i < n; i++) {
		if (a[i] < 0) printf("%d  ", a[i]);
	}
}