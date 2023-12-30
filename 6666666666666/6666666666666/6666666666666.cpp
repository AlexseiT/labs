#include <iostream>
#include <stdlib.h>
#include <ctime>
using namespace std;

void printMas(float* a, int n, float* b) {
	for (int i = 0; i < n; ++i) 
		cout << a[(int)b[i]] << endl;
}
void printMas2(float* a, int n) {
	printf("Massive without changes\n");
	for (int i = 0; i < n; ++i) 
		cout << a[i] << endl;
}
int main() {
	srand(time(NULL));
	int n, i, j;
	cin >> n;
	float* a = new float[n];
	float* b = new float[n];
	for (i = 0; i < n; ++i) {
		a[i] = (float)rand() / RAND_MAX;
		b[i] = a[i];
	}
	for (i = 0; i < n; i++) {
		for (j = 0; j < n - i - 1; j++) {
			if (b[j] > b[j + 1]) {
				float temp = b[j];
				b[j] = b[j + 1];
				b[j + 1] = temp;
			}
		}
	}
	for (i = 0; i < n; ++i) {
		for (j = 0; j < n; ++j) {
			if (a[i] == b[j]) b[j] = i;
		}
	}
	printMas(a, n, b);
	printMas2(a, n);

	delete a;
	delete b;
}