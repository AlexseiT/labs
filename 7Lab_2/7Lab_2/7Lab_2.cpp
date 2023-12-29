#include <iostream>
#include <stdlib.h>
#include <ctime>
using namespace std;



int random(int a, int b) {
	int c = a + rand() % (b - a);
	return c;
}

void checkSum(int** C, int n) {
	int i, j;
	int sum;
	for (i = 0; i < n; ++i) {
		sum = 0;
		for (j = 1; j < C[i][0] + 1; ++j) {
			C[i][C[i][0] + 1] += C[i][j];
		}
	}
	for (i = 0; i < n; ++i) {
		cout << "sum "<< i << " : " << C[i][C[i][0] + 1] << "\n";
	}
}

int main() {
	srand(time(NULL));

	int i, n, j;
	cin >> n;

	cout << endl;

	int* B = new int[n];

	for (i = 0; i < n; ++i) {

		B[i] = random(2, 10);

		cout << B[i] << endl;

	}

	cout << endl;

	int** C = new int* [n];

	for (i = 0; i < n; ++i) {

		C[i] = new int[B[i] + 2];

		C[i][0] = B[i];
	}

	for (i = 0; i < n; ++i) {

		for (j = 1; j < C[i][0] + 1; ++j) {

			C[i][j] = random(10, 1000);

			cout << C[i][j] << " ";
		}
		cout << "\n";
	}
	cout << endl;

	checkSum(C, n);

	system("pause");
}
