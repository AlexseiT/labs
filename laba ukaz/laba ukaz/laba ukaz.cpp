#include <iostream>
#include <stdlib.h>
#include <ctime>
using namespace std;
int i, j, n;
void inline printMas(float **b, int n) {
	for (i = 0; i < n; ++i) printf("%f\n", *(b[i]));
}
void inline Fillrand(float **b, float* a, int n) {
	for (i = 0; i < n; ++i) {
		a[i] = (float)rand() / RAND_MAX + rand() % 1000000;
		b[i] = &a[i];
	}
}
void qsort(float **b, int n) {
	int i = 0;
	int j = n - 1;
	float* mid = b[n / 2];
	do {
		while (*b[i] < *mid) {
			i++;
		}
		while (*b[j] > * mid) {
			j--;
		}
		if (i <= j) {
			float* tmp = b[i];
			b[i] = b[j];
			b[j] = tmp;
			i++;
			j--;
		}
	} while (i <= j);
	if (j > 0) {
		qsort(b, j + 1);
	}
	if (i < n) {
		qsort(&b[i], n - i);
	}
}
int main() {
	srand(time(NULL));
	cin >> n;
	float* a = new float[n];
	float** b = new float* [n];
	Fillrand(b, a, n);
	printMas(b, n);
	qsort(b, n);
	cout << endl;
	printMas(b, n);
}
