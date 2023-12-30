#include <iostream>
#include <time.h>

using namespace std;

int** genRandMatrix(int size, int maxValue) {

	int** arr = new int* [size];

	for (int i = 0; i < size; i++) {

		int size = rand() % 10;

		arr[i] = new int[size + 1];

		arr[i][0] = size;

		for (int j = 1; j < size + 1; j++) {

			arr[i][j] = rand() % 10;

		}
	}
	return arr;
}


void printMatrix(int** matrix, int size) {
	cout << size << endl;
	for (int i = 0; i < size; i++) {
		cout << matrix[i][0] << " : ";
		for (int j = 1; j < matrix[i][0] + 1; j++) {
			cout << matrix[i][j] << "\t";
		}
		cout << endl;
	}
}


int main() {
	srand(time(NULL));
	int size = rand() % 10;
	int maxValue = 100;
	int** matrix = genRandMatrix(size, maxValue);
	printMatrix(matrix, size);
	delete[] matrix;
}