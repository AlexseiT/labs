#include <iostream>
#include <stdlib.h>
#include <ctime>
using namespace std;

double printMas(float** b, int n) {
	for (int i = 0; i < n; ++i) cout <<* (b[i]) << endl;
}

int main() {
	srand(time(NULL));
	int n, i;
	cin >> n;
	float* a = new float[n];
	float** b = new float* [n];
	for (i = 0; i < n; ++i) {
		a[i] = (float)rand() / RAND_MAX;
		b[i] = &a[i];
	}
	for (i = 1; i < n; i++) {
		for (int j = i; j > 0 && *b[j - 1] > * b[j]; j--) {
			float* tmp = b[j - 1];
			b[j - 1] = b[j];
			b[j] = tmp;
		}
	}
	printMas(b, n);
}