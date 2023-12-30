#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <math.h>

int random(int N) { return rand() % N; }
const int n = 20;

int main() {
	int   i, x = 0, y = 10;
	float a[n];
	for (int i = 0; i < n; i++) {
		a[i] = (float)rand() * (y - x) / RAND_MAX + x;
		printf("%2.2f   ", a[i]);
	}
	printf("\n");
	for (int i = 1; i < n-1; i++) {
		if (a[i] > a[i + 1] && a[i] > a[i - 1]) printf("%2.2f  ", a[i]);
	}
}